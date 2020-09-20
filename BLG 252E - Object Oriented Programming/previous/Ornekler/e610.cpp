// e610.cpp
// Multiple Inheritance 
#include<iostream>
using namespace std;

class Base1{        // Base 1
 public:
	int a;
	void fa1(){cout << "Base1 fa1" << endl;}
	char *fa2(int){cout << "Base1 fa2" << endl;return 0;}
};

class Base2{      // Base 2
 public:
	int a;
	char *fa2(int, char){cout << "Base2 fa2" << endl;return 0;}
	int fc(){cout << "Base2 fc" << endl;return 0;}
};

// ** Deriv is derived from Base1 and Base1 **
class Deriv : public Base1 , public Base2{
 public:
	int a;
	float fa1(float){cout << "Deriv fa1" << endl;return 1.0;}
	int fb1(int){cout << "Deriv fb1" << endl;return 0;}
};

int main()
{
	Deriv d;
	d.a=4;								//Deriv::a
	d.Base2::a=5;						//Base2::a
	float y=d.fa1(3.14);				// Deriv::fa1
	int i=d.fc();						// Base2::fc
	//char *c = d.fa2(1);			// ERROR
	return 0;
}
