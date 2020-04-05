#include "openbabel/plugin.h"
#include "openbabel/format.h"
#include "openbabel/obconversion.h"
#include "openbabel/mol.h"
#include "openbabel/forcefield.h"
#include "openbabel/builder.h"

using namespace std;
using namespace OpenBabel;


namespace OpenBabel
{

// Wrapper of OB classes to bind them to JavaScript
class ObBaseHelper
{
private:
	OBBase* fObBase;
public:
	ObBaseHelper()
	{
	}
	ObBaseHelper(OBBase* obBase)
	{
		this->fObBase = obBase;
	}
	void setOBBaseObj(OBBase* obBase)
	{
		this->fObBase = obBase;
	}
	int getDataSize()
	{
		return this->fObBase->DataSize();
	}
	OBGenericData* getDataAt(int index)
	{
		std::vector<OBGenericData*> data = this->fObBase->GetData();
		return data[index];
	}
	std::string getTitle()
	{
		const char* p = this->fObBase->GetTitle();
		std::string s(p);
		return s;
	}
	void setTitle(std::string s)
	{
		this->fObBase->SetTitle(s.c_str());
	}
};

// some utility functions
class ObUtils
{
public:
	static std::string getAtomType(OBAtom* atom)
	{
		char* s = atom->GetType();
		std::string str(s);
		return str;
	}
};


struct ObFormatInfo
{
	std::string id;
	std::string mimeType;
	std::string description;
	std::string specificationURL;
};

/*
class ObFormatUtil
{
public:
	static int getFormatCount(std::string inOrOut)
	{
	}
	static ObFormatInfo getFormatInfo(int index)
	{
	}
}
*/

class ObFormatWrapper
{
private:
	OBFormat *obFormat;
public:
	ObFormatWrapper() {}
	ObFormatWrapper(OBFormat *obFormat) { this->obFormat = obFormat; }
	//~ObFormatWrapper() { delete this->obFormat; }

	OBFormat* getObFormat() { return this->obFormat; }
	void setObFormat(OBFormat* value) { this->obFormat = value; }

	std::string getId()
	{
		std::string s(this->obFormat->GetID());
		return s;
	}
	std::string getDescription()
	{
		std::string s(this->obFormat->Description());
		return s;
	}
	std::string getTargetClassDescription()
	{
		std::string s(this->obFormat->TargetClassDescription());
		return s;
	}
	std::string getSpecificationURL()
	{
		std::string s(this->obFormat->SpecificationURL());
		return s;
	}
	std::string getMIMEType()
	{
		std::string s(this->obFormat->GetMIMEType());
		return s;
	}
	std::string getTypeName()
	{
		const std::type_info& info = this->obFormat->GetType();
		std::string s(info.name());
		return s;
	}
};

class ObConversionWrapper
{
private:
	OBConversion* obConv;
	ObFormatWrapper inFormatWrapper, outFormatWrapper;
	std::istringstream* inStream = NULL;
	std::stringstream* outStream = NULL;
protected:
	OBFormat* getOBFormat(std::string mimeType = "", std::string fileExt = "")
	{	
		OBFormat *fmt = NULL;
		if (mimeType.length())
			fmt = obConv->FormatFromMIME(mimeType.c_str());
		
		if (!fmt && fileExt.length())
			fmt = obConv->FormatFromExt(fileExt);
		if (fmt)
			return fmt;
		else
			return NULL;
	}
public:
	ObConversionWrapper() 
	{
		this->obConv = new OBConversion();
		this->inStream = new istringstream();
		this->outStream = new stringstream();
		this->obConv->SetOutStream(this->outStream);
	};
	~ObConversionWrapper() 
	{
		//cout << "Delete obConv";
		delete this->obConv;
		//cout << "Delete obConv done";
		
		if (this->inStream)
		{
			//cout << "Delete inStream";
			delete this->inStream;
			//cout << "Delete inStream done";
		}
		
		if (this->outStream)
		{
			//cout << "Delete outStream";
			delete this->outStream;
			//cout << "Delete outStream done";
		}
	};

	ObFormatInfo getFormatInfoById(std::string id)
	{
		OBFormat* fmt = this->obConv->FindFormat(id);
		ObFormatInfo result;
		result.id = id;
		result.description = fmt->FirstLine(fmt->Description());
		const char* pc = fmt->GetMIMEType();
		if (strlen(pc) > 2)  // less then 3 chars is not a legal mime type
		{
			// correct some MIME type mistakes in original OpenBabel code
			if ((id == "sd") || (id == "sdf"))
				result.mimeType = "chemical/x-mdl-sdfile";
			else
			{
				std::string s(pc);
				result.mimeType = s;
			}
		}
		else
			result.mimeType = "";
		result.specificationURL = fmt->SpecificationURL();
		return result;
	}

	ObFormatWrapper* getInFormat() { return &this->inFormatWrapper; }
	ObFormatWrapper* getOutFormat() { return &this->outFormatWrapper; }

	// Set input format by mimeType or fileExt, returns format id of OpenBabel
	ObFormatWrapper* setInFormat(std::string mimeType = "", std::string fileExt = "")
	{
		OBFormat *fmt = this->getOBFormat(mimeType, fileExt);
		if (fmt)
		{
			this->obConv->SetInFormat(fmt);
			this->inFormatWrapper.setObFormat(fmt);
			//return fmt->GetID();
			return &this->inFormatWrapper;
		}
		else
			return NULL;
	}
	// Set output format by mimeType or fileExt, returns format id of OpenBabel
	ObFormatWrapper* setOutFormat(std::string mimeType = "", std::string fileExt = "")
	{
		OBFormat *fmt = this->getOBFormat(mimeType, fileExt);
		if (fmt)
		{
			this->obConv->SetOutFormat(fmt);
			//return fmt->GetID();
			//return (new ObFormatWrapper(fmt));
			this->outFormatWrapper.setObFormat(fmt);
			return &this->outFormatWrapper;
		}
		else
			return NULL;
	}

	bool readString(OBBase* obj, std::string input)
	{
		return this->obConv->ReadString(obj, input);
	}
	std::string writeString(OBBase* obj, bool trimWhitespace = false)
	{
		return this->obConv->WriteString(obj, trimWhitespace);
	}

	void setInStr(std:: string input)
	{
		if (this->inStream)
		{
			//cout << "Delete inStream before set";
			delete this->inStream;
			this->inStream = NULL;
			//cout << "Delete inStream before set done";
		}
		//if (!this->inStream)
		{
			//cout << "Create new inStream";
			this->inStream = new std::istringstream(input);
			//cout << "Create new inStream done";
		}
		
		this->obConv->SetInStream(this->inStream);
	}
	std::string getOutStr()
	{
		/*
		if (!this->outStream)
			return "";
		else
		*/
		
		{
			return this->outStream->str();
		}
	}
	void clearOut()
	{
		this->outStream->clear();
		this->outStream->str("");
		//this->obConv->SetOutStream(this->outStream);
	}
	/*
	int convert()
	{
		if (this->outStream)
			delete outStream;
		this->outStream = new std::ostringstream();
		this->obConv.SetOutStream(this->outStream);
		return this->obConv.Convert();
	}
	OBBase* getChemObject()
	{
		return this->obConv.GetChemObject();
	}
	bool isLastChemObject()
	{
		return this->obConv.IsLast();
	}
	bool isFirstChemObject()
	{
		return this->obConv.IsFirst
	}
	*/

	bool readFromInput(OBBase* obObj)
	{
		return this->obConv->Read(obObj, this->inStream);
	}

	bool writeToOutput(OBBase* obObj)
	{		
		if (!this->obConv->GetOutStream())
			this->obConv->SetOutStream(this->outStream);
				
		return this->obConv->Write(obObj); //, this->outStream);
	}

	std::string getSupportedInputFormatsStr(std::string delimiter = "|")
	{
		std::vector<std::string> fmts = obConv->GetSupportedInputFormat();

		string result = "", s = "";
		int i = 0;
		for (vector<std::string>::iterator iter=fmts.begin();iter!=fmts.end();iter++)
		{
			if (i != 0)
				result.append(delimiter);
			s = *iter;
			result.append(s);			
			++i;
		}
		return result;
	}
	std::string getSupportedOutputFormatsStr(std::string delimiter = "|")
	{
		std::vector<std::string> fmts = this->obConv->GetSupportedOutputFormat();

		string result = "", s = "";
		int i = 0;
		for (vector<std::string>::iterator iter=fmts.begin();iter!=fmts.end();iter++)
		{
			if (i != 0)
				result.append(delimiter);
			s = *iter;
			result.append(s);			
			++i;
		}
		return result;
	}
	
	/*
	std::string getOptions(OBConversion::Option_type opttyp = OBConversion::Option_type::OUTOPTIONS)
	{
		return this->conv->GetOptions(opttype);
	}
	*/
	
	void addOption(std::string optionName, OBConversion::Option_type opttyp = OBConversion::Option_type::OUTOPTIONS, std::string optionValue = NULL)
	{
		return this->obConv->AddOption(optionName.c_str(), opttyp, optionValue.c_str());
	}
	
	bool removeOption(std::string optionName, OBConversion::Option_type opttyp = OBConversion::Option_type::OUTOPTIONS)
	{
		return this->obConv->RemoveOption(optionName.c_str(), opttyp);
	}
	
	void setOptions(std::string options, OBConversion::Option_type opttyp = OBConversion::Option_type::OUTOPTIONS)
	{
		return this->obConv->SetOptions(options.c_str(), opttyp);
	}
};


class OB3DGenWrapper
{
//private:
	//OBForceField* pFF;
//private:
	//const char* defForceFieldName = "MMFF94";
public:
	// Generate 3D coord for molecule
	// On success, 0 will be returned, otherwise returns values less than 0
	int generate3DStructure(OBMol* pmol, std::string forceFieldName = "MMFF94")
	{
		std::string ff = forceFieldName;
		if (ff == "")
			ff = "MMFF94";  // default force field
		OBForceField* pFF = OBForceField::FindForceField(ff);
		if (!pFF) 
		{
			return -1;  // can not run
		}

		pFF->SetLogFile(&cerr);
		pFF->SetLogLevel(OBFF_LOGLVL_LOW);		

		OBBuilder builder;
		builder.Build(*pmol);

		pmol->AddHydrogens(false, true); // hydrogens must be added before Setup(mol) is called
		
		if (!pFF->Setup(*pmol)) 
		{
			return -2;
		}
		pFF->SteepestDescent(500, 1.0e-4); 
		pFF->WeightedRotorSearch(250, 50);
		pFF->SteepestDescent(500, 1.0e-6);

		pFF->UpdateCoordinates(*pmol);

		/*
		if (pmol->Has3D())
			obErrorLog.ThrowError(__FUNCTION__, "Has 3D" + std::to_string(pmol->NumAtoms()), obWarning);
		else
			obErrorLog.ThrowError(__FUNCTION__, "Has 2D" + std::to_string(pmol->NumAtoms()), obWarning);
		*/

		return 0;  // success
	}
	OBMol* generate3DStructureFromMolData(std::string molData, std::string forceFieldName = "MMFF94")
	{
		ObConversionWrapper conv;
		conv.setInFormat("", "mol");

		OBMol* obMol = new OBMol();
		conv.readString(obMol, molData);
		if (this->generate3DStructure(obMol, forceFieldName) >= 0)
			return obMol;
		else
			return NULL;
	}
};


}
