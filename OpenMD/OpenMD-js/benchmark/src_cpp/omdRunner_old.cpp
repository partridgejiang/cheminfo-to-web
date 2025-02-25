#include <fstream>
#include <iostream>
#include <locale>
#include "utils/simError.h"
#include "utils/CaseConversion.hpp"
#include "utils/Revision.hpp"
#include "brains/Register.hpp"
#include "brains/SimCreator.hpp"
#include "brains/SimInfo.hpp"
#include "constraints/ZconstraintForceManager.hpp"
#include "restraints/RestraintForceManager.hpp"
#include "integrators/IntegratorFactory.hpp"
#include "integrators/Integrator.hpp"
#include "optimization/OptimizationFactory.hpp"
#include "optimization/Method.hpp"
#include "optimization/Constraint.hpp"
#include "optimization/Problem.hpp"
#include "optimization/PotentialEnergyObjectiveFunction.hpp"
#include "restraints/ThermoIntegrationForceManager.hpp"

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

using namespace OpenMD;
using namespace QuantLib;

int main(int argc, char* argv[]){
  
  // first things first, all of the initializations

#ifdef IS_MPI
  MPI_Init( &argc, &argv ); // the MPI communicators
#endif
   
  initSimError();           // the error handler
  
  Revision r;

#ifdef IS_MPI
  if( worldRank == 0 ){
#endif
    std::cout << 
      "  +--------------------------------------------------------------------------+\n"<<
      "  |    ____                    __  ___ ____                                  |\n"<<
      "  |   / __ \\____  ___  ____   /  |/  // __ \\  The Open Molecular Dynamics    |\n"<<
      "  |  / / / / __ \\/ _ \\/ __ \\ / /|_/ // / / /  Engine (formerly OOPSE).       |\n"<<
      "  | / /_/ / /_/ /  __/ / / // /  / // /_/ /                                  |\n"<<
      "  | \\____/ .___/\\___/_/ /_//_/  /_//_____/    Copyright 2004-2017 by the     |\n"<<
      "  |     /_/                                   University of Notre Dame.      |\n"<<
      "  |           http://openmd.org                                              |\n"<<
      "  |                                                                          |\n"<<
      "  |   " << r.getFullRevision() << "       |\n" <<
      "  |               " << r.getBuildDate() <<  "                       |\n" <<
      "  |                                                                          |\n"<<
      "  | OpenMD is an OpenScience project.  All source code is available for any  |\n"<<
      "  | use whatsoever under a BSD-style license.                                |\n"<<
      "  |                                                                          |\n"<<
      "  | Support OpenScience!  If you use OpenMD or its source code in your       |\n"<<
      "  | research, please cite the appropriate papers when you publish your work. |\n"<<
      "  | Good starting points for code and simulation methodology are:            |\n"<<
      "  |                                                                          |\n"<<
      "  | [1] Meineke, et al., J. Comp. Chem. 26, 252-271 (2005).                  |\n"<<
      "  | [2] Fennell & Gezelter, J. Chem. Phys. 124, 234104 (2006).               |\n"<<
      "  | [3] Sun, Lin & Gezelter, J. Chem. Phys. 128, 234107 (2008).              |\n"<<
      "  | [4] Vardeman, Stocker & Gezelter, J. Chem. Theory Comput. 7, 834 (2011). |\n"<<
      "  | [5] Kuang & Gezelter, Mol. Phys., 110, 691-701 (2012).                   |\n"<<
      "  | [6] Lamichhane, Gezelter & Newman, J. Chem. Phys. 141, 134109 (2014).    |\n"<<
      "  | [7] Lamichhane, Newman & Gezelter, J. Chem. Phys. 141, 134110 (2014).    |\n"<<
      "  +--------------------------------------------------------------------------+\n"<<
      "\n";
    
    if( argc < 2 ){
      strcpy( painCave.errMsg,
              "No meta-data file was specified on the command line.\n" );
      painCave.isFatal = 1;
      simError();
    }
#ifdef IS_MPI
  }
#endif

  // EMCC file system	
	#ifdef __EMSCRIPTEN__
	EM_ASM(
		FS.mkdir('/curr');		
		FS.mount(NODEFS, { root: '.' }, '/curr');		
		FS.mkdir('/FRC_ROOT');
		FS.mount(NODEFS, { root: '/usr/local/openmd/forceFields' }, '/FRC_ROOT');
	);
	string rootDir = "/curr/";
	#else
	string rootDir = "";
	#endif	
  
  strcpy( checkPointMsg, "Successful number of arguments" );
  errorCheckPoint();

  //register forcefields, integrators and minimizers
  registerAll();

  //create simulation model
  string inputFileName = rootDir;
  inputFileName += argv[1];
  
  SimCreator creator;
  SimInfo* info = creator.createSim(inputFileName);

  Globals* simParams = info->getSimParams();
  MinimizerParameters* miniPars = simParams->getMinimizerParameters();

  if (miniPars->getUseMinimizer() && simParams->haveEnsemble()) {
    sprintf(painCave.errMsg,
            "Ensemble keyword can not co-exist with useMinimizer = \"true\" in the minimizer block\n");
    painCave.isFatal = 1;
    simError();        
  }

  if (miniPars->getUseMinimizer()) {
    //create minimizer
    OptimizationMethod* myMinimizer =OptimizationFactory::getInstance()->createOptimization(toUpperCopy(miniPars->getMethod()), info);

    if (myMinimizer == NULL) {
      sprintf(painCave.errMsg,
              "Optimization Factory can not create %s OptimizationMethod\n",
	      miniPars->getMethod().c_str());
      painCave.isFatal = 1;
      simError();
    }

    ForceManager* fman = new ForceManager(info);      
    fman->initialize();

    PotentialEnergyObjectiveFunction potObjf(info, fman); 
    DumpStatusFunction dsf(info);
    DynamicVector<RealType> initCoords = potObjf.setInitialCoords();
    Problem problem(potObjf, *(new NoConstraint()), dsf, initCoords);


    int maxIter = miniPars->getMaxIterations();
    int mssIter = miniPars->getMaxStationaryStateIterations();
    RealType rEps = miniPars->getRootEpsilon();
    RealType fEps = miniPars->getFunctionEpsilon();
    RealType gnEps = miniPars->getGradientNormEpsilon();

    EndCriteria endCriteria(maxIter, mssIter, rEps, fEps, gnEps); 

    myMinimizer->minimize(problem, endCriteria);

    delete myMinimizer;
  } else if (simParams->haveEnsemble()) {
    //create Integrator

    Integrator* myIntegrator = IntegratorFactory::getInstance()->createIntegrator(toUpperCopy(simParams->getEnsemble()), info);
 
    if (myIntegrator == NULL) {
      sprintf(painCave.errMsg,
              "Integrator Factory can not create %s Integrator\n",
	      simParams->getEnsemble().c_str());
      painCave.isFatal = 1;
      simError();
    }
                
    //Thermodynamic Integration Method
    //set the force manager for thermodynamic integration if specified
    if (simParams->getUseThermodynamicIntegration()){
      ForceManager* fman = new ThermoIntegrationForceManager(info);
      myIntegrator->setForceManager(fman);
    }

    // Restraints
    if (simParams->getUseRestraints() &&
        !simParams->getUseThermodynamicIntegration()) {
      ForceManager* fman = new RestraintForceManager(info);
      myIntegrator->setForceManager(fman);
    }

    //Zconstraint-Method
    if (simParams->getNZconsStamps() > 0) {
      info->setNZconstraint(simParams->getNZconsStamps());
      ForceManager* fman = new ZconstraintForceManager(info);
      myIntegrator->setForceManager(fman);
    }
        
    myIntegrator->integrate();
    delete myIntegrator;
  }else {
    sprintf(painCave.errMsg,
            "Integrator Factory can not create %s Integrator\n",
            simParams->getEnsemble().c_str());
    painCave.isFatal = 1;
    simError();
  }
    
  delete info;


  strcpy( checkPointMsg, "Great googly moogly!  It worked!" );
  errorCheckPoint();

#ifdef IS_MPI  
  MPI_Finalize();
#endif

  return 0 ;
}
