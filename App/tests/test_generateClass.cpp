#include "..\src\GenerateClass.h"
#include <iostream>

using namespace std;

int main(){
	string name = "Testing";
	GenerateClass test = GenerateClass(name);
	test.createFile();
	return 0;
}
