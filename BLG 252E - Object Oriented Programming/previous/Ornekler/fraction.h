// fraction.h (e413)
// http://www.buzluca.info/oop
// Decleration of fractions
#ifndef _fraction_           // to include only once
#define _fraction_

class Fraction{       // A class to define fractions
   int numerator,denominator;
 public:
   Fraction(int, int);
	void print() const;
};

#endif