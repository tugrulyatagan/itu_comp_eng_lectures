// e57.cpp
//	 Overloading of unary preincrement operator ++
// This operator increments the real part of a complex number by 0.1

#include <iostream>
using namespace std;

class ComplexT{
	 double re,im;
 public:
	 ComplexT(double re_in=0,double im_in=1): re(re_in),im(im_in)
		{};									// Constructor
	 const ComplexT& operator++();	// ++ operator increments the real part by 0.1
	 void print() const;					// prints complex number on the screen
};

// ++ operator
// increments the real part of a complex number by 0.1
// returns a reference to object to be able to use the operator in an assignment statement
const ComplexT & ComplexT::operator++()
{
	re=re+0.1;
	return *this;
}

// prints complex number on the screen
void ComplexT::print() const     
{
	cout << re << " , " << im << endl;
}

// ----- Main function -----
int main()
{
	ComplexT z1(1.2,0.5),z2;
	cout << "Before operation z1 = ";
	z1.print();
	z2= ++z1;								// operator ++ is called
	cout << "After operation" << endl;
	cout << "z1 = ";
	z1.print();
	cout << "z2 = ";
	z2.print();
	return 0;
}
