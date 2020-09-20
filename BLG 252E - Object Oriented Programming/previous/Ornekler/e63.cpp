// e63.cpp
// Overriding members of base class 

#include <iostream>
using namespace std;

class A{						// Base class
 public:
   int ia1,ia2;
   void fa1();
   int fa2(int);
};

class B: public A{		// Derived class
 public:
   float ia1;           // overrides ia1
   float fa1(float);		// overloads fa1
};

// --- Methods of A ---
void A::fa1()
{
	cout << "fa1 of A has been called" << endl;
}

int A::fa2(int i)
{
	cout << "fa2 of A has been called" << endl;
	return i;
}


// --- Methods of B ---
float B::fa1(float f)
{
	cout << "fa1 of A has been called" << endl;
	return f;
}

// ----- Main Function -----
int main()
{
	B b;
	int j=b.fa2(1);			// A::fa2
	b.ia1=4;						// float fa1 of B
	b.ia2=3;						// ia2 of A. If it is public
	float y=b.fa1(3.14);		// OK, fa1 of B is called
	//b.fa1();					// ERROR! fa1 of B needs a floar argument
	b.A::fa1();			
	b.A::fa1();
	b.A::ia1=1;
	return 0;
}