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

string loadFile(string fileName)
{
	ifstream fin(fileName);
	if (! fin.is_open())
		{ cout << "Error opening file" << fileName << endl; return ""; }  
	ostringstream sin;
	sin <<  fin.rdbuf();
	string result = sin.str();
	fin.close();
	return result;
}

//int runOmdJob(string inFileName)
int runOmdJob(char* srcFileNames[], int srcFileCount)  // note: srcFileNames[0] is exe name
{
	// The first file should be input file (.omd), others are included file (.inc)
	string inFileName = srcFileNames[1];
	/*
	ifstream fin(inFileName);
	if (! fin.is_open())
		{ cout << "Error opening file" << inFileName << endl; return 1; }  
	ostringstream sin;
	sin <<  fin.rdbuf();
	
	string omd = sin.str();
	fin.close();
	*/
	string omd = loadFile(inFileName);	
	
	//cout << inFileName << endl << omd << endl;
	
	OpenMdRunner runner;
	
	clock_t tStart = clock();
	runner.runOmdJob(omd);
	clock_t tEnd = clock();
	float execTime = (tEnd - tStart) / CLOCKS_PER_SEC;
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
	//include files
	ptree ptIncFiles, ptIncData;
	int i;
	string incFileName;
	for (i = 2; i < srcFileCount; ++i)
	{
		incFileName = srcFileNames[i];
		int pos = incFileName.find_last_of('/');
		string coreFileName(incFileName.substr(pos + 1));
		string data = loadFile(incFileName);
		if (data != "")
		{
			ptIncData.put("id", coreFileName);
			ptIncData.put("content", data);			
		}
		ptIncFiles.push_back(std::make_pair("", ptIncData));
	}
	ptRoot.add_child("incFiles", ptIncFiles);
	
	string outFileName = inFileName + ".json";
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
	
	if (argc < 2)
	{
		cout << "Usage: omTestDataBuilder input.omd [inc1.inc inc2.inc...]" << endl;
		return 0;
	}
	/*
	int i = 0;	
	for (i = 1; i < argc; ++i)
	{
		inFileName = argv[i];
		runOmdJob(inFileName);
	}
	*/
	cout << "Starting calculation job..." << endl;
	runOmdJob(argv, argc);
	
	return 0;
}
