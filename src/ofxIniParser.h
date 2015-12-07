//ofxIniParser
//
//enrico<nas3a>viola 2015

#pragma once
#include "ofMain.h"

class ofxIniParser{
public:

	typedef map<string, string> IniKeys;
	typedef map<string, IniKeys> IniSections; 

	ofxIniParser();
	bool load(string _pth);
	void save(string _pth);
	inline void save(){save(pth);}
	static bool parseKeyLine(string & l, string & key, string & val);
	
	void pushSection(string secName);
	void popSection();
	inline bool isInSection(){return curSection!="";}
	inline bool sectionExists(string secName){return (iniSections.count(secName)>0);}
	inline bool isLoaded(){return bLoaded;}

	inline string getValueString(string section, string key){return iniSections[section][key];}
	inline int getValueInt(string section, string key){return ofToInt(getValueString(section, key));}
	inline float getValueFloat(string section, string key){return ofToFloat(getValueString(section, key));}
	inline bool getValueBool(string section, string key){return ofToBool(getValueString(section, key));}

	inline string getValue(string key, string defVal){return isInSection()?getValueString(curSection,key):defVal;}
	inline int getValue(string key, int defVal){return isInSection()?getValueInt(curSection,key):defVal;}
	inline float getValue(string key, float defVal){return isInSection()?getValueFloat(curSection,key):defVal;}
	inline bool getValue(string key, bool defVal){return isInSection()?getValueBool(curSection,key):defVal;}

	inline void setValueString(string section, string key, string val){iniSections[section][key]=val;}
	inline void setValueString(string key, string val){if(isInSection())setValueString(curSection,key,val);}

	template<typename T>
	inline void setValue(string section, string key, T val, int precision=0){setValueString(section, key, ofToString(val,precision));}

	template<typename T>
	inline void setValue(string key, T val, int precision=0){setValueString(key,ofToString(val,precision));}


	inline static bool isLineSection(string & l){
		return (l[0]=='[' && l[l.length()-1]==']');
	}
	
	inline static string getSectionName(string & l){
		return l.substr(1,l.length()-2);
	}
protected:
	IniSections iniSections;
	string pth;
	string curSection;
	bool bLoaded;
};