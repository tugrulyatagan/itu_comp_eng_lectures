// complex.cpp (e413)
// http://www.buzluca.info/oop
//	Objetcs as a members of other classes 

#include<iostream>
#include"fraction.h"
#include"complex.h"
using namespace std;


// Constructor
// first, constructors of the member objects must be called
ComplexFraction::ComplexFraction(int re_in,int im_in):re(re_in,1),im(im_in,1)
{
    cout << "Constructor of ComplexFraction" << endl;
}

// Prints complex numbers on the screen
// print function of the member objects are called
void ComplexFraction::print() const
{
   re.print();  
   im.print();  
}
