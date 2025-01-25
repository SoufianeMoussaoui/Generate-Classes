#pragma once 

#include <iostream>
#include <string>
#include <vector>

#include <windows.h>
#include <shlobj.h> 
#include <fstream>
#include <unordered_map>
#include <any>
#include <stdexcept>

using namespace std;


class GenerateClass{
private:
	string className;
	unordered_map<string, any> attributesListe;
public:
	GenerateClass() = default;
	GenerateClass(const string&);
	~GenerateClass() = default;

	void setClassName(string);
	string getClassName() const;
	string getFileName();
  
	void createFile();

    bool attributeExiste();
	void createGetter(ofstream&);
	void createSetter(ofstream&);

    void copieFile();
	void clearFile();
    friend string getDesktopPath();
    void setAttribute();
	
};

// Function to simplfier the complexity : 


string constructorByDefault(string&);
string constructorByCopie(string&);
string destructor(string&);






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


