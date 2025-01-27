#pragma once 

#include <iostream>
#include <string>
#include <vector>

//#include <windows.h>
//#include <shlobj.h> 
#include <fstream>
#include <unordered_map>
#include <any>
#include <stdexcept>

using namespace std;


class GenerateClass{
private:
        string className;
        bool port, clDef;
public:

        unordered_map<string, any> attributesListe;
        vector<string> attDec;
        GenerateClass() =default;
        GenerateClass(const string&, bool pr = false, bool def = false);
        ~GenerateClass() = default;

        void setClassName(string);
        string getClassName() const;
        string getFileName();
    void setAttributesDecl();
        void createFile();

    bool attributeExiste();
        void createGetter(vector<string>&);
        void createSetter(vector<string>&);

    void copieFile();
    void clearFile();
    //friend string getDesktopPath();
    void setAttribute();
    
    void createFileDef();
    void clearFileDef();
    string getFileNameCpp() const;
    
};




// Function to simplfier the complexity : 

string decDisF(); 

string constructorByDefault(string&);
string constructorByCopie(string&);
string destructor(string&);
string constructorByArgument(string&);
string getVarType(const any&);





/*

Create by just the class name:

    -- In public : 

                -- 2 constructor :
                        ClassName();
                        ClassName(ClassName&);
                -- destructor : 
                        ~ClassName();

If the user need attributes : 

        -- By default the attributes set private

    -- need the type of the each attribute 

    -- add To the file :

        -- constructor by argument : 
                ClassName(type, ...)

*/



/*

["type getVarName() cosnt;", ... ]

["void setVarName(type);", ...]

*/







