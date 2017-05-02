#include <fstream>
#include <iostream>
#include <locale>
#include <stdio.h>
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

#include "adapters.h"

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

namespace OpenMD {

	string getOpenMdAdapterWorkingDir()
	{
		#ifdef __EMSCRIPTEN__
		return FS_WORKING_DIR; 
		#else
		return ".";
		#endif
	}

//class OpenMdRunner 
	// private
	string OpenMdRunner::getDataFileName(string fileExt, string baseFileName)
	{		
		if (baseFileName == "")
			return this->dataFileBaseName + "." + fileExt;
		else
			return baseFileName + "." + fileExt;
	}
	// file name for input
	string OpenMdRunner::getInputFileName(string baseFileName)
	{
		return this->getDataFileName("omd", baseFileName);		
	}
	// file names of output
	/*
	string getDumpFileName(string baseFileName = NULL)
	{		
		return this->getDataFileName("dump", baseFileName);
	}
	string getEorFileName(string baseFileName = NULL)
	{
		return this->getDataFileName("eor", baseFileName);
	}
	string getReportFileName(string baseFileName = NULL)
	{
		return this->getDataFileName("report", baseFileName);
	}
	string getStatFileName(string baseFileName = NULL)
	{
		return this->getDataFileName("stat", baseFileName);
	}
	*/
	string OpenMdRunner::saveDataToFile(string data, string fileName)
	{				
		ofstream dataFileWriter(fileName);  
		if (dataFileWriter.is_open())   
		{
			dataFileWriter << data;			 
			dataFileWriter.close();  
		}
		return fileName;
	}
	
	// Set input data of OMD job
	string OpenMdRunner::setInputData(string omdData)
	{		
		// create input file for SimCreator
		string currDir = getOpenMdAdapterWorkingDir();
		this->dataFileBaseName = currDir + "/" + OpenMdRunner::defDataFileBaseName;
		string dataFileName = this->getInputFileName(this->dataFileBaseName);
		/*
		ofstream dataFileWriter(dataFileName);  
		if (dataFileWriter.is_open())   
		{
			dataFileWriter << omdData;			 
			dataFileWriter.close();  
		}
		return dataFileName;
		*/
		this->saveDataToFile(omdData, dataFileName);
		return dataFileName;
	}	
	// public
	OpenMdRunner::OpenMdRunner()
	{
	}

	// add include file to current workspace
	void OpenMdRunner::addIncludeData(string data, string dataFileId)
	{
		string currDir = getOpenMdAdapterWorkingDir();
		this->saveDataToFile(data, currDir + "/" + dataFileId);
	}
	void OpenMdRunner::removeIncludeData(string dataFileId)
	{
		string currDir = getOpenMdAdapterWorkingDir();
		string fname = currDir + "/" + dataFileId;
		remove(fname.c_str());
	}

	// The following method get output data of calculation, must be called after runOmdJob
	string OpenMdRunner::getOutputData(string outputFileType)
	{
		string fileName = this->getDataFileName(outputFileType);
		ifstream fin(fileName);  
		if (!fin.is_open())  
			{ cerr << "Error opening file: " << fileName << endl; return ""; }  
		ostringstream sin;
		sin <<  fin.rdbuf();
		string str = sin.str();
		fin.close();
		fin.clear();
		return str;
	}
	string OpenMdRunner::getDumpData()
	{
		return this->getOutputData("dump");
	}
	string OpenMdRunner::getEorData()
	{
		return this->getOutputData("eor");
	}
	string OpenMdRunner::getReportData()
	{
		return this->getOutputData("report");
	}
	string OpenMdRunner::getStatData()
	{
		return this->getOutputData("stat");
	}
	// run OMD calculation job based on omdData, actually a modification of main function of OpenMD program
	int OpenMdRunner::runOmdJob(string omdData)
	{
		initSimError();           // the error handler		 
		Revision r;

		#ifdef IS_MPI
		  if( worldRank == 0 ){
		#endif
			if( omdData == "" ){
			  strcpy( painCave.errMsg,
					  "No meta-data file was specified.\n" );
			  painCave.isFatal = 1;
			  simError();
			  return 0;
			}
		#ifdef IS_MPI
		  }
		#endif
		
		strcpy( checkPointMsg, "Successful OMD input data" );
		errorCheckPoint();

		//register forcefields, integrators and minimizers
		registerAll();

		// create input file for SimCreator if essential		
		string inputFileName = this->setInputData(omdData);

		//create simulation model		
		SimCreator creator;
		SimInfo* info = creator.createSim(inputFileName);

		Globals* simParams = info->getSimParams();
		MinimizerParameters* miniPars = simParams->getMinimizerParameters();

		if (miniPars->getUseMinimizer() && simParams->haveEnsemble()) {
			sprintf(painCave.errMsg,
					"Ensemble keyword can not co-exist with useMinimizer = \"true\" in the minimizer block\n");
			painCave.isFatal = 1;
			simError();
			return 0;
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
			  return 0;
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
		} 
		else if (simParams->haveEnsemble()) 
		{
			//create Integrator

			Integrator* myIntegrator = IntegratorFactory::getInstance()->createIntegrator(toUpperCopy(simParams->getEnsemble()), info);

			if (myIntegrator == NULL) {
			  sprintf(painCave.errMsg,
					  "Integrator Factory can not create %s Integrator\n",
				  simParams->getEnsemble().c_str());
			  painCave.isFatal = 1;
			  simError();
			  return 0;
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
		}
		else
		{
			sprintf(painCave.errMsg,
					"Integrator Factory can not create %s Integrator\n",
					simParams->getEnsemble().c_str());
			painCave.isFatal = 1;
			simError();
			return 0;
		}

		delete info;


		strcpy( checkPointMsg, "Great googly moogly!  It worked!" );
		errorCheckPoint();

		#ifdef IS_MPI  
		MPI_Finalize();
		#endif

		return 1;  // success
	}	
}  // endif namespace
