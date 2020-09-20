// e85.cpp
// non-virtual function used as base class destructor 
#include <iostream>
using namespace std;

class Base{
 public:
	 int data;
	 virtual void f(){}
	 ~Base() { cout << "Base destructor" << endl; }   // Destructor is not virtual
};
class Base2{
 public:
	 int data;
	 virtual void f(){}
	 ~Base2() { cout << "Base destructor" << endl; }   // Destructor is not virtual
};
class Derived : public Base,public Base2{
 public:
	 int data;
	 void f(){}
	 ~Derived() { cout << "Derived destructor" << endl; } // Non-virtual
};

int main()
{
  Base* pb;					 // pb can point to objects of Base ans Derived
  pb = new Derived;		 // pb points to an oject of Derived
  delete pb;
  cout << "Program terminates" << endl;
  return 0;
}
