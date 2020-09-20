/********************************************************
* ornek   : 3-0                                         *
* aciklama: operator oncelikleri					    *
* derleme : g++ -o program_ismi 0.cpp                   *
********************************************************/
#include <iostream>

using namespace std;

int main()
{
	int x, y, z;
	
	z = 1;
	x = y = z;
	cout << "x = " << x << " \t y = " << y << " \t z = " << z << endl;
	
	x = ++y + ++z;
	cout << "x = " << x << " \t y = " << y << " \t z = " << z << endl;

	x = y == z;
	cout << "x = " << x << " \t y = " << y << " \t z = " << z << endl;
	
	x = y == --z;
	cout << "x = " << x << " \t y = " << y << " \t z = " << z << endl;
	
	return 0;
}
