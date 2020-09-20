// complex.h (e413)
// http://www.buzluca.info/oop
// Decleration of complex numbers

#ifndef _complex_           // to include only once
#define _complex_

#include "fraction.h"           // decleration of Fraction is necesary

class ComplexFraction{			//  Complex numbers: has two fractions
	Fraction re,im;			    //  member objects
 public:
	ComplexFraction(int,int);  // Constructor
	void print() const;
};

#endif