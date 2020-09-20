// e58.cpp
// Overloading of unary preincrement and postincrement operator ++ 
// This operator increments the real part of a complex number by 0.1

#include<iostream>
using namespace std;

class ComplexT{
	double re,im;
 public:
	ComplexT(double re_in=0,double im_in=0): re(re_in),im(im_in)
		{};									// Constructor
	const ComplexT& operator++();	// preincrement ++
	ComplexT operator++(int);			// postincrement ++
	void print() const;					// prints complex numbers on the screen

};

// preincrement ++
const ComplexT & ComplexT::operator++()  
{
	re=re+0.1;
	return *this;
}

// postincrement ++
ComplexT  ComplexT::operator++(int)  
{
	ComplexT temp;
	temp=*this;     // saves old value
	re=re+0.1;
	return temp;     // return old value
}

// prints complex number on the screen
void ComplexT::print() const     // constant print function
{
	cout << re << " , " << im << endl;
}

// ----- Main Function -----
int main()
{
	ComplexT z1(1.2,0.5),z2;
	z2= ++z1;						// operator++() is called
	cout << "After preincrement operation:" << endl;
	cout <<"z1 =";
	z1.print();
	cout <<"z2 =";
	z2.print();
	z2= z1++;						// operator++(int) is called
	cout << "After postincrement operation:" << endl;
	cout <<"z1 =";
	z1.print();
	cout <<"z2 =";
	z2.print();
	return 0;
}