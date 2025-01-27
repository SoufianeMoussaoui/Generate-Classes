#include "GenerateClass.h"
#include "GenerateClassDef.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <any>
#include <stdexcept>
#include <string>
//#include <windows.h>
//#include <shlobj.h> 
#include <typeinfo>

using namespace std;


GenerateClass::GenerateClass(const string& className, bool pr, bool def): className(className)
, port(pr), clDef(def){}


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

    if(attributeExiste()){
       setAttributesDecl();
       bool check = true;
       // Private attribute
        if(!port){
            check = false;
            headerFile << "\rprivate : " << endl;
            for(int i = 0;i<attDec.size(); i++)
                headerFile << "\t" << attDec[i] << endl;
        }
        else if(port){
            headerFile << "\rpublic : " << endl;
            for(int i = 0;i<attDec.size(); i++)
                headerFile << "\t" << attDec[i] << endl;
        }
        if(!check)
            headerFile << "\rpublic : "  <<endl;
    }

    headerFile << "\r\t" << constructorByDefault(className) << endl;
    headerFile << "\t" << constructorByCopie(className) << endl;
    headerFile << "\t" << destructor(className) << endl;
    if(attributeExiste()){ // Add Constructor by arguments and getters/setters
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
      headerFile <<  "\t" << decDisF() << ";" << endl;
    }
    headerFile << "\r};" << endl;
    if(clDef)
      createFileDef();
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
string decDisF(){return "void display() const"}



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

void GenerateClass::setAttributesDecl(){
    if(attDec.size() != 0){
        cerr << "The attribute";
        return;
    }
    for(auto it = attributesListe.begin(); it != attributesListe.end(); ++it){
        string att = getVarType(it->second) + " " + it->first + ";";
        attDec.push_back(att);
    }

}


string GenerateClass::getFileNameCpp() const {return className + ".cpp"};


void GenerateClass::createFileDef(){
  // all methods must be called once
  GenerateClassDef definition;
  definition.setClassDefName(className);
  
  string filename = getFileNameCpp();
  ofstream file(filename);
  if(!file.is_open()){
    cerr << "Error opening the file";
    return;
  } 
  
  string incHeder = "#include \""+ getFileName()  + "\""; 
  file << incHeder <<"#include <iostream>" << endl <<"#include <string>" << endl;
  file << "using namespace std;" << endl;

  definition.getConstr(attributeExiste());
  for(int i = 0;i<definition.Constructors.size(); i++)
    file << "\r" << definition.Constructors[i] << endl;
  
  if(attributeExiste()){
    for(int i = 0;i<definition.GS.size(); i++)
        file << "\r" <<definition.GS[i] << endl;
    file << "\r" << definition.getDisplay() << endl;
  }
  
}


void GenerateClass::clearFileDef(){
    string filename = getFileNameCpp();
    ofstream file(filename, ios::trunc);
    if (!file.is_open()) {
        cerr << "Error opening file!" << endl;
        return;
    }
    file.close();
}

