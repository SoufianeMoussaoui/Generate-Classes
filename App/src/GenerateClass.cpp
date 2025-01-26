#include "GenerateClass.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <any>
#include <stdexcept>
#include <string>
#include <windows.h>
#include <shlobj.h> 
#include <typeinfo>

using namespace std;


GenerateClass::GenerateClass(const string& className, bool port = false): className(className){}

void GenerateClass::setClassName(string Name){className = Name;}
string GenerateClass::getClassName() const{return className;}
string GenerateClass::getFileName(){return className + ".h";}



void GenerateClass::createFile(){

	string filename = getFileName();
	ofstream headerFile(filename);
	if(!headerFile.is_open()){
		cerr << "Error opening file!" << endl;
        return;
	}
	// The header of the file:
	headerFile << "#pragma once" << endl << "#include <iostream>" << endl <<"#include <string>" << endl;
	headerFile << "using namespace std;" << endl;
    headerFile << "\rclass " << className << "{" << endl;
    // check if there is anay attribute
    
    /*if(attributeExiste()){
    	if(!port){
    		// private
    	}
    	
    }
    */
    headerFile << "\rpublic : " << endl << "\r\t" << constructorByDefault(className) << endl;
    headerFile << "\t" << constructorByCopie(className) << endl;
    headerFile << "\t" << destructor(className) << endl;
    if(attributeExiste()){
    	headerFile << "\t" << constructorByArgument(className);
    	for (auto it = attributesListe.begin(); it != attributesListe.end(); ++it){
    		auto test = it;
    		if (++test == attributesListe.end())
    			headerFile << getVarType(it->second);
    		else
    			headerFile << getVarType(it->second) << ", ";
    	}
    	headerFile << ");" << endl;

    	vector<string> getters;
    	vector<string> setters;
    	createGetter(getters);
    	createSetter(setters);

    	headerFile << "\t\r//Getters : " << endl;
    	for(int i = 0; i<getters.size(); i++)
    		headerFile << "\t" << getters[i] << endl;
 
    	headerFile << "\t\r//Setters: " << endl;
    	for(int i = 0; i<setters.size(); i++)
    		headerFile << "\t" << setters[i] << endl;

    }
    headerFile << "\r};" << endl;
}


void GenerateClass::clearFile(){
	string filename = getFileName();
	ofstream headerFile(filename, ios::trunc);
    if (!headerFile.is_open()) {
        cerr << "Error opening file!" << endl;
        return;
    }
    headerFile.close();
}


bool GenerateClass::attributeExiste(){return !(attributesListe.empty());}

string constructorByDefault(string& name){return name + "();";}
string constructorByCopie(string& name){return name + "(" + name + "&);";}
string destructor(string& name){return "~" + name + "();";}
string constructorByArgument(string& name){return name + "(";}

string getDesktopPath() {
    char path[MAX_PATH];
    if (SHGetFolderPathA(NULL, CSIDL_DESKTOPDIRECTORY, NULL, 0, path) == S_OK) {
        return std::string(path);
    }
    return "";
}

string getVarType(const any& value){
	if (value.type() == typeid(int))
        return "int";
    else if (value.type() == typeid(string)) 
        return "string";
    else 
        return "double";
    
}



void GenerateClass::createGetter(vector<string>& getters){
	for(auto it = attributesListe.begin(); it != attributesListe.end(); ++it){
		string getFunction = getVarType(it->second) + " get" + it->first + "() const;";
		getters.push_back(getFunction);
	}
}
void GenerateClass::createSetter(vector<string>& setters){
	for(auto it = attributesListe.begin(); it != attributesListe.end(); ++it){
		string setFunction = "void set" + it->first + "(" + getVarType(it->second) + ");" ;
		setters.push_back(setFunction);
	}
}


	
