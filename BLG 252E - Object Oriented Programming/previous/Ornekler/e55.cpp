// e55.cpp
// Function call operator with no arguments 
// It prints complex numbers on the screen

#include <iostream>
using namespace std;

// A class to define complex numbers
class ComplexT{
	double re,im;					// real and imaginary parts
 public:
	ComplexT(double re_new=0,double im_new=0):re(re_new),im(im_new)	// Constructor
		{ };
	ComplexT operator+(const ComplexT & ) const;    // + operatot
	void operator()() const;   // The Function call operator with no arguments
};

// + operator
ComplexT ComplexT::operator+(const ComplexT &c) const
{
	double re_temp, im_temp;				// temporary variables
	re_temp = re+c.re;
	im_temp=im+c.im;
	return ComplexT(re_temp,im_temp);	// constructs and returns the result object
}

// operator ()
// prints complex numbers on the screen
void ComplexT::operator()() const
{
	cout << "complex number= " << re << " , " << im << endl ;
}

// ----- Main function -----
int main()
{
 ComplexT z1(1,1), z2(2,2), z3;
	z1();
	z2();
	z3 = z1 + z2;
	z3();
	return 0;
}