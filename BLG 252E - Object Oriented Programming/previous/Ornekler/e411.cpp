// e411.cpp
// http://www.buzluca.info/oop
// nested objects , orders of constructors and destructors
#include <iostream>
using namespace std;

// The inner class 
class classA{
 public:
	 classA(){ cout << endl<< "Constructor Class A";}
	 ~classA(){ cout << endl<< "Destructor Class A";}
};

// The enclosing class. Contains two objects of class A as members 
class classB{
	 classA m1,m2;    // Two member objects
 public:
	 classB(){ cout << endl<< "Constructor Class B";}
	 ~classB(){ cout << endl<< "Destructor Class B";}
};

// ----- Main Function -----
int main()
{
	classB objecOfB;
	return 0;
}