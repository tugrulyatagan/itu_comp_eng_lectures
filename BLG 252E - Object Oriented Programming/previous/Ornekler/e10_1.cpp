// e10_1.cpp
// http://www.buzluca.info/oop
//   Example1 for Exceptions

#include <iostream>
using namespace std;

float fraction(int num, int denom)
{
	if(denom==0) throw "Divide by zero";
	return static_cast<float>(num)/denom;
}

int main()
{
	int numerator,denominator;
	cout << endl << "Enter the numerator ";
	cin >> numerator;
	cout << endl << "Enter the denominator ";
	cin >> denominator;
	try{
		cout << fraction(numerator,denominator);
	}
	catch (const char* result){
		cout << endl << result;
	}
	cout << endl << "End of Program";
	return 0;
}