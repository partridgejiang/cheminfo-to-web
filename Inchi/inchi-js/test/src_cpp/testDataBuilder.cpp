#include <fstream>
#include <iostream>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include "../../inchi-src/INCHI-1-SRC/INCHI_BASE/src/inchi_api.h"

extern "C"
{
#include "../src/inchi_js_utils.h"
}

using namespace std;
using namespace boost::property_tree;

#define MAX_COL_SIZE 512

string processMolBlock(string molBlock)
{
	char* inputBlock = const_cast<char*>(molBlock.c_str());	
	char options[1] = "";	
	
	string result = molToInchiJson(inputBlock, options);
	return result;
}

int runJobs(string inputFileName, string outputFileName)
{
	char buffer[MAX_COL_SIZE];
	ifstream in(inputFileName);  
	if (! in.is_open())  
		{ cout << "Error opening file: " << inputFileName; return 1; }
		
	ptree ptRoot;
	ptree ptContainer;
	ptree ptItem;
	
	// read in SDF and split it into multiple part of mol data blocks, then process
	string currLine = "";
	string currMolBlock = "";
	string blockResult;
	bool molBegins = 1;
	int i = 0;
	while (true)
	{
		//in.getline(buffer, MAX_COL_SIZE);		
		//currLine = buffer;
		getline(in, currLine);
		//cout << currLine << endl;
		//cout << "----" << currLine.find(">") << " : " << currLine.find("$") << endl;
		//if (buffer[0] == '<' || in.eof())   // begin of property line, indicating the end of a MOL block
		if (currLine.find(">") == 0 || in.eof())
		{
			//cout << "molEnds" << endl;
			molBegins = 0;
			if (currMolBlock != "")
			{
				++i;
				blockResult = processMolBlock(currMolBlock);
				ptItem.put("molData", currMolBlock);
				ptItem.put("inchiResult", blockResult);
				ptContainer.push_back(std::make_pair("", ptItem));
				currMolBlock = "";
				cout << "Molecule [" << i << "]" << endl;
				cout << blockResult << endl;
				if (in.eof())
					break;
			}
		}
		//else if (buffer[0] == '$')  // mark of start of next mol
		else if (currLine.find("$$$$") == 0)  // mark of start of next mol
		{
			//cout << "molBegins" << endl;
			molBegins = 1;
			currMolBlock = "";
		}
		else
		{
			if (molBegins)
				currMolBlock += currLine + "\n";
			//cout << "[]" << currLine << endl;
		}		
		
		if (in.eof())
			break;
	}
	
	ptRoot.add_child("data", ptContainer);
	
	//cout << currMolBlock << endl;
	
	ofstream fout(outputFileName);
	if (!fout.is_open())   
    {
		cout << "Error opening file" << outputFileName << endl;
		return 1;         
    }
    write_json(fout, ptRoot);
	fout.close();
	
	return 0;
}

int main(int argc, char* argv[]){
	if (argc < 3)
	{
		cout << "You must specify the input SDF and output result file name." << endl;
		return 1;
	}
	
	FILE *file;	
	string inFileName = argv[1];
	string outFileName = argv[2];
	runJobs(inFileName, outFileName);	
	
	return 0;
}
