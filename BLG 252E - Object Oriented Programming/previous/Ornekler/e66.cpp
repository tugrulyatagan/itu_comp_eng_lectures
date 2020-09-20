// e66.cpp
// Destructors and Inheritance
#include <iostream>
using namespace std;

class Parent {
  public:
	Parent() { cout << "Parent constructor" << endl; }
	~Parent() { cout << "Parent destructor" << endl; }
};

class Child : public Parent {
  public:
	Child() { cout << "Child constructor" << endl; }
	~Child() { cout << "Child destructor" << endl; }
};

int main()
{
	cout << "Start" << endl;
	Child ch;				// create a Child object
	cout << "End" << endl;
	return 0;
} 
