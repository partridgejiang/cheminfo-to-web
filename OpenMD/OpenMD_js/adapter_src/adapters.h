#ifndef OPENMD_JS_ADAPTER_H
#define OPENMD_JS_ADAPTER_H

#define FS_WORKING_DIR "." /*"current"*/

using namespace std;

namespace OpenMD {

	string getOpenMdAdapterWorkingDir();	
	
	class OpenMdRunner {
	public:
		OpenMdRunner();
		void addIncludeData(string data, string dataFileId);
		void removeIncludeData(string dataFileId);
		string getOutputData(string outputFileType);
		string getDumpData();
		string getEorData();
		string getReportData();
		string getStatData();
		int runOmdJob(string omdData);		
	private:
		const string defDataFileBaseName = "__omd_data__";
		string dataFileBaseName;
		string getDataFileName(string fileExt, string baseFileName = "");
		string getInputFileName(string baseFileName = "");
		string saveDataToFile(string data, string fileName);
		string setInputData(string omdData);
	};

}  // namespace

#endif  // end of OPENMD_JS_ADAPTER_H 