// e64.cpp
// Defult constructors in inheritance 

#include <iostream>
using namespace std;

////////////////////////////////////////////////////
class Parent
{
	public:
		Parent()
			{ cout << endl<< "   Parent constructor"; }
};
////////////////////////////////////////////////////
class Child : public Parent
{
	public:
		Child()
			{ cout << endl<<"   Child constructor"; }
};
// ----- Main function -----
int main()
{
	cout <<  endl<<"Starting";
	Child ch;                 // create a Child object
	cout <<  endl<<"Terminating";
	return 0;
}