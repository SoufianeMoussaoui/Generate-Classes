#include "GenerateClassDef.h"
#include "GenerateClass.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <any>
#include <stdexcept>
#include <string>
#include <cctype> 
//#include <windows.h>
//#include <shlobj.h> 
#include <typeinfo>

using namespace std;








string GenerateClassDef::getDisplay(){
	string Disp = decDisF() +  "{";
	for(auto it = attributesListe.begin(); it != attributesListe.end(); ++it)
		Disp += "\r\t cout << " + it->first + "<< endl;";
	Disp += "}";
	return Disp;
}


void GenerateClassDef::setClassDefName(string name){this->name = name;}


void GenerateClassDef::getConstr(bool att){
    string tmpConstr = name + "::" + name + "(){cout <<  \"constructeur par defaut\" << endl;}";
    Constructors.push_back(tmpConstr);
    tmpConstr = name + "::~" + name + "(){cout <<  \"Objet est detruite\" << endl;}";
    Constructors.push_back(tmpConstr);
    if (att){
    	
    	tmpConstr = name + "::" + name + "(";
    	string tmpConstParam = ":";
        string tmpConstCopie = tmpConstr + name + "& " + toUpper(name) + ") : ";
    	for(auto it = attributesListe.begin(); it != attributesListe.end(); ++it){
    		auto test = it;++test;
        	if (test == attributesListe.end()){
        		tmpConstr += getVarType(it->second) + " " + it->first;
    			tmpConstParam +=   it->first + "(" + it->first + "){}";
    			tmpConstCopie += it->first + "(" + toUpper(name) + "." + it->first + ") {}";
    		}
    		else{
    			tmpConstr += getVarType(it->second) + " " + it->first + ", ";
    			tmpConstParam +=   it->first + "(" + it->first + "),";
    			tmpConstCopie += it->first + "(" + toUpper(name) + "." + it->first + "),";
    		}
    	}
    	tmpConstr +=  ")" + tmpConstParam;
    	Constructors.push_back(tmpConstr);
        Constructors.push_back(tmpConstCopie);
    	addStGt();
    }

}

void GenerateClassDef::addStGt(){
	string setters, getters;
	for(auto it = attributesListe.begin(); it != attributesListe.end(); ++it){
    	setters = "void set" + it->first + "(" + getVarType(it->second) + it->first + "){this->" + it->first + " = " + it->first + ";}";
    	getters = getVarType(it->second) + " get" + it->first + "() const {return" + it->first + ";}"; 
    	GS.push_back(setters);
    	GS.push_back(getters);           
    }
}



string toUpper(const string& str) {
    string result = str;
    for (char& ch : result) {
        ch = toupper(ch); 
    }
    return result;
}
