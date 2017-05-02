#include <fstream>
#include <iostream>
#include <locale>
#include <time.h>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
//#include <boost/foreach.hpp>

#include "adapters.h"

using namespace std;
using namespace OpenMD;
//using namespace QuantLib;

using namespace boost::property_tree;

int runOmdJob(string inFileName)
{
	ifstream fin(inFileName);
	if (! fin.is_open())
		{ cout << "Error opening file" << inFileName << endl; return 1; }  
	ostringstream sin;
	sin <<  fin.rdbuf();
	
	string omd = sin.str();
	fin.close();
	
	OpenMdRunner runner;
	
	clock_t tStart = clock();
	runner.runOmdJob(omd);
	clock_t tEnd = clock();
	int execTime = (tEnd - tStart) / CLOCKS_PER_SEC;
	printf("Run calculation in %d sec.\n", execTime);	
	string stat = runner.getStatData();
	string report = runner.getReportData();
	string dump = runner.getDumpData();
	string eor = runner.getEorData();
	
	// write result to JSON
	ptree ptRoot;
	ptRoot.put("omd", omd);
	ptRoot.put("report", report);
	ptRoot.put("stat", stat);
	ptRoot.put("eor", eor);
	ptRoot.put("dump", dump);
	ptRoot.put<float>("execTime", execTime);
	
	string outFileName = inFileName + ".result";
	ofstream fout(outFileName);
	if (!fout.is_open())   
    {
		cout << "Error opening file" << outFileName << endl;
		return 1;         
    }
    write_json(fout, ptRoot);
	fout.close();
	
	return 0;
}

int main(int argc, char* argv[]){
	FILE *file;
	string inFileName;
	int i = 0;
	for (i = 1; i < argc; ++i)
	{
		inFileName = argv[i];
		runOmdJob(inFileName);
	}
	
	return 0;
}
