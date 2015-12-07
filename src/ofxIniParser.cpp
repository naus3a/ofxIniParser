//ofxIniParser
//
//enrico<nas3a>viola 2015

#include "ofxIniParser.h"

ofxIniParser::ofxIniParser(){
	pth="";
	curSection = "";
	bLoaded = false;
}

bool ofxIniParser::load(string _pth){
	bLoaded = false;

	if(ofFile::doesFileExist(_pth)){
		bLoaded = true;
		pth = _pth;
		
		iniSections.clear();

		ofBuffer buf = ofBufferFromFile(_pth);
		while(!buf.isLastLine()){
			string line = buf.getNextLine();
			if(line.length()>2){
				if(isLineSection(line)){
					string secName = getSectionName(line);
					iniSections.insert(std::pair<string, IniKeys>(secName,IniKeys()));
					curSection = secName;
				}else{
					if(isInSection()){
						string key;
						string val;
						if(parseKeyLine(line, key, val)){
							iniSections[curSection].insert(std::pair<string, string>(key, val));
						}
					}
				}
			}
		}
		popSection();
		/*IniSections::iterator is;
		IniKeys::iterator ik;
		for(is=iniSections.begin();is!=iniSections.end();++is){
			cout<<"["<<is->first<<"]"<<endl;
			IniKeys keys = is->second;
			for(ik=keys.begin();ik!=keys.end();++ik){
				cout<<"- "<<ik->first<<"="<<ik->second<<endl;
			}
		}*/
	}

	return bLoaded;
}

void ofxIniParser::save(string _pth){
	pth = _pth;
	string s;
	IniSections::iterator is;
	IniKeys::iterator ik;
	stringstream ss;
	for(is=iniSections.begin();is!=iniSections.end();++is){
		ss<<"["<<is->first<<"]"<<endl;
		IniKeys keys = is->second;
		for(ik=keys.begin();ik!=keys.end();++ik){
			ss<<ik->first<<"="<<ik->second<<endl;
		}
	}
	ofBuffer buf;
	buf.set(ss);
	ofBufferToFile(_pth,buf);
}

void ofxIniParser::pushSection(string secName){
	curSection = secName;
}

void ofxIniParser::popSection(){
	curSection = "";
}

bool ofxIniParser::parseKeyLine(string & l, string & key, string & val){
	bool b=false;
	key = "";
	val = "";
	size_t found = l.find('=');
	if(found!=string::npos){
		key = l.substr(0,found);
		val = l.substr(found+1,l.length());
		b = true;
	}
	return b;
}

