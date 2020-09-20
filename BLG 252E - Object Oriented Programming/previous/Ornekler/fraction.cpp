// fraction.cpp (e413)
// http://www.buzluca.info/oop
// Definition of fraction class

#include<iostream>
#include"fraction.h"
using namespace std;

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