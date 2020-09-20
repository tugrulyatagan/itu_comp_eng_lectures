// e412.cpp
// http://www.buzluca.info/oop
// Pointers to objetcs as a members of other classes 

#include<iostream>
using namespace std;

class Fraction{       // A class to define fractions
   int numerator,denominator;
 public:
   Fraction(int, int);
	void print() const;
};

Fraction::Fraction(int num, int denom)    // CONSTRUCTOR
{
	numerator=num;
	if (denom==0) denominator=1;
	else denominator=denom;
		 cout << "Constructor of Fraction" << endl;
}

void Fraction ::print() const
{
	cout << numerator << "/" << denominator << endl;
}

class ComplexFraction{			//  Complex numbers: has two fractions
	Fraction *re, *im;			//  pointers to objects
 public:
	ComplexFraction(int,int);    // Constructor
	void print() const;
	~ComplexFraction();    // Destructor
 };

// Constructor
// first, constructors of the member objects must be called
ComplexFraction::ComplexFraction(int re_in,int im_in)
{
	re= new Fraction(re_in,1);
	im= new Fraction(im_in,1);
	cout << "Constructor of ComplexFraction" << endl;
}

// Prints complex numbers on the screen
// print function of the member objects are called
void ComplexFraction::print() const
{
   re->print();  
   im->print();  
}

 // Destructor
ComplexFraction::~ComplexFraction()
{
	delete re;
	delete im;
	cout << "Destructor of ComplexFraction" << endl;
}
//----- Main Function -----
int main()
{
	ComplexFraction cf(2,5);			// A complex number is created
	cf.print();							// Complex number is printed on the screen
	return 0;
}
