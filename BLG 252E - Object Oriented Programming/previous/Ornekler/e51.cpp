// e51.cpp
//	Overloading of operator + 
#include <iostream>
using namespace std;

class ComplexT{
	 double re,im;
 public:
	 ComplexT(double re_in=0,double im_in=1);      // Constructor
	 ComplexT operator+(const ComplexT & ) const; // Function of operator +
	 void print() const;
};

// Default Constructor
ComplexT::ComplexT(double re_in, double im_in)
{
	re=re_in;
	im=im_in;
	cout<< endl << "Default Constructor";
}

// function for operator + 
ComplexT ComplexT::operator+(const ComplexT &c) const
{
	double re_new, im_new;
	re_new=re+c.re;
	im_new=im+c.im;
	return ComplexT(re_new,im_new);
}

void ComplexT::print() const
{
	cout << endl << "re=" << re << " im=" << im;
}

int main()
{
 ComplexT z1(1,1),z2(2,2),z3;
 z3=z1+z2;								// like z3 = z1.operator+(z2);
 z3.print();
 return 0;
}