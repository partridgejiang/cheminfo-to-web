#include <fstream>
#include <iostream>
#include <locale>
#include <time.h>
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

using namespace OpenMD;
using namespace QuantLib;

int main(int argc, char* argv[]){
	FILE *file;
	string inFileName = argv[1];
	ifstream fin(inFileName);
	if (! fin.is_open())  
		{ cout << "Error opening file"; return 1; }  
	ostringstream sin;
	sin <<  fin.rdbuf();
	
	string sData = sin.str();
	fin.close();
	
	OpenMdRunner runner;
	
	clock_t tStart = clock();
	runner.runOmdJob(sData);
	clock_t tEnd = clock();
	int execTime = (tEnd - tStart) / CLOCKS_PER_SEC;
	printf("Run calculation in %d sec.\n", execTime);
	/*
	string stat = runner.getStatData();
	cout << stat;
	*/
	
	return 0;
}
