// e52.cpp
// Overloading the assignmet opertor for complex Numbers
//	Actually overloading of this opertor for complex numbers is usless
// Operator provided by the compiler does the same job 

#include <iostream>
using namespace std;

class ComplexT{		// A class to define complex numbers
	double re,im;
 public:
	ComplexT(double re_new=0,double im_new=0):re(re_new),im(im_new)
	{}															// Constructor
	void operator=(const ComplexT& );				//assingment operator
	ComplexT operator+(const ComplexT & ) const; // Function of operator +
	void print() const;
};

// Function for operator =
// Compiler provides the same function
// The main program rus correctly even if this function is deleted
void ComplexT::operator=(const ComplexT& z)
{
	 re = z.re;
	 im = z.im;
	 cout << "Assignment operator has been invoked" << endl;
}

// function for operator + 
ComplexT ComplexT::operator+(const ComplexT &c) const
{
	cout << "Operator + is called" << endl;
	double re_new, im_new;
	re_new=re+c.re;
	im_new=im+c.im;
	return ComplexT(re_new,im_new);
}

void ComplexT::print() const
{
	cout << "complex number= " << re << " , " << im << endl;
}

int main()
{
	ComplexT z1, z2(1,2);
	cout << "Before assignment:" << endl;
	z1.print();
	z1=z2;
	cout << "After assignment:" << endl;
	z1.print();
	ComplexT z3;
	cout << "Addition:" << endl;
	z3 = z1 + z2;
	z3.print();
	return 0;
}