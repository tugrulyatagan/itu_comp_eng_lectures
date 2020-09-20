// e67.cpp
// Constructors and destructors in a chain of classes
#include <iostream>
using namespace std;

class A
{
 private:
	int intA;
	float floA;
 public:
	A(int i, float f) :
				 intA(i), floA(f)                    // initialize A
	 { cout << "Constructor A" << endl;  }
	void display()
	 { cout << intA << ", " << floA << "; "; }
	~A()                                       // Destructor
	 { cout << endl << "Destructor A";  }
};

// ******* B is derived from A ********
class B : public A
{
 private:
	int intB;
	float floB;
 public:
	B(int i1, float f1, int i2, float f2) :
				 A(i1, f1),                         // initialize A
				 intB(i2), floB(f2)                 // initialize B
	 { cout << "Constructor B" << endl; }
	void display()
	 {
		 A::display();
		 cout << intB << ", " << floB << "; ";
	 }
	~B()                                       // Destructor
	 { cout << endl << "Destructor B";  }
};

//******** C is derives from B ***********
class C : public B
{
 private:
	int intC;
	float floC;
 public:
	C(int i1, float f1, int i2, float f2, int i3, float f3) :
				 B(i1, f1, i2, f2),                 // initialize Parent
				 intC(i3), floC(f3)                 // initialize Child
	 { cout << "Constructor C" << endl; }
	void display()
	 {
		 B::display();
		 cout << intC << ", " << floC;
	 }
	~C()                                       // Destructor
	 { cout << endl << "Destructor C";  }
};

int main()
{
	C c(1, 1.1, 2, 2.2, 3, 3.3);
	cout << endl<< "Data in c = ";
	c.display();
	return 0;
}