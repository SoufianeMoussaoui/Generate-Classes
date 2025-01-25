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

using namespace std;


GenerateClass::GenerateClass(const string& className): className(className){}

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
    headerFile << "\rclass " << className << "{" << endl;
    // check if there is anay attribute
  
    	headerFile << "\rpublic : " << endl << "\r\t" << constructorByDefault(className) << endl;
    	headerFile << "\t" << constructorByCopie(className) << endl;
    	headerFile << "\t" << destructor(className) << endl;
    	headerFile << "};" << endl;

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


//bool GenerateClass::attributeExiste(){return attributesListe.size() > 0;}

string constructorByDefault(string& name){return name + "();";}
string constructorByCopie(string& name){return name + "(" + name + "&);";}
string destructor(string& name){return "~" + name + "();";}

string getDesktopPath() {
    char path[MAX_PATH];
    if (SHGetFolderPathA(NULL, CSIDL_DESKTOPDIRECTORY, NULL, 0, path) == S_OK) {
        return std::string(path);
    }
    return "";
}







	