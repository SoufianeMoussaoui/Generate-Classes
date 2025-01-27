#pragma once
#include "GenerateClass.h"


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



class GenerateClassDef : public GenerateClass{

public:
    string name;
    vector<string> Constructors;
    vector<string> GS;
	GenerateClassDef() = default;
	~GenerateClassDef() = default;
 

    void getConstr(bool);
    string getDisplay();
    void setClassDefName(string);
    void addStGt();
    

	
};

string toUpper(const string&);






