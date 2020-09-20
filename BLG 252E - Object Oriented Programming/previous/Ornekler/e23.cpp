// e23.cpp
// http://www.buzluca.info/oop
// Overloading of function names
#include <iostream>
using namespace std;

struct ComplexT{        // Structure for complex numbers
    float re,im;
};

void print (float value){   // print function for real numbers
   cout << "value= " << value << endl;
}
void print (ComplexT c){    // print function for complex numbers
   cout << "real= " << c.re << " im= " << c.im << endl;
}
void print (float value, char c){    // print function for real numbers and chars
   cout << "value= " << value << " c= " << c << endl;
}
//--------- Main Function ----------
int main()
{
	ComplexT z;			// A complex number is defined
	z.re=0.5;			// Fields of the complex number are filled
	z.im=1.2;			// 
	print(z);			// For complex number
	print(4.2);			// for real number
	print(2.5,'A');	// for real number and char
	return 0;
}
