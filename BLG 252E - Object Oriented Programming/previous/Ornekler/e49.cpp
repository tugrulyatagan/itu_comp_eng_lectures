// e49.cpp
// http://www.buzluca.info/oop
//	Avaoding temporary objects

#include <iostream>
using namespace std;

class ComplexT{							// A class to define complex numbers
	 double re,im;							// real and imaginer part of a complex num
	 static unsigned int counter;		// count the number of objects of this class
 public:
	 ComplexT(double re_in=0,double im_in=1); // Constructor
	 ComplexT(const ComplexT &);		// Copy Constructor
	 ComplexT add(const ComplexT &) const;	// A method takes an object by reference
	 void print() const;					// Prints complex numbers on the screen	
	 static void reset(){counter=0;}	// A static function to reset the static member counter
	 ~ComplexT();							// Destructor
};

// Constructor. Can be called without any argument
ComplexT::ComplexT(double re_in, double im_in)
{
	re=re_in;
	im=im_in;
	counter++;								// Increment number of objects
	cout<< endl << "Default Constructor";
	cout<< "  Num. of current objects = "<< counter;
}
// Copy Constructor
ComplexT::ComplexT(const ComplexT &c)
{
	re=c.re;
	im=c.im;
	counter++;								// Increment number of objects
	cout<< endl << "Copy Constructor";
	cout<< "  Num. of current objects = "<< counter;
}

// The add method: Adds two complex numbers and creates a third complex number as a result
// This function takes a reference to an object
ComplexT ComplexT::add(const ComplexT &c) const
{
	cout<< endl << "Add function is called";
	double  re_new,im_new;				// Only data items are created
   re_new = re + c.re;
   im_new = im + c.im;
   return ComplexT(re_new,im_new);      	// Constructor is called
}

// Prints the complex number on the screen
void ComplexT::print() const
{
	cout << endl << "re= " << re << " , im= " << im;
	cout<< "  Num. of current objects = "<< counter;
}

// Destructor
// Decrements the number of the current objects
ComplexT::~ComplexT()
{
	counter--;						// Decrements the number of current objects
	cout<< endl << "Destructor has been invoked";
	cout<< "  Num. of current objects = "<< counter;
}

unsigned int ComplexT::counter; // Memory allocation for the static member

// ----- Main Function -----
int main()
{
	ComplexT::reset();			// clear the counter
	ComplexT z1(1,2) , z2(0.5, -1) ,z3;	// Three objects are defined
	z3=z1.add(z2);					// z3 = z1 + z2
	z3.print();
	return 0;
}
