/****************************************
* ornek   : 8-1							*
* aciklama: pointer ornegi				*
* derleme : g++ -o program_ismi 1.cpp	*
****************************************/

#include <iostream>
using namespace std;

int main()
{
	int n = 44;
	
	cout << "n = " << n << endl << "&n = " << &n << endl;

	int* pn;
	pn= &n;

	int m = *pn;

	cout << "*pn = " << m << endl << "pn = " << pn << endl << "&pn = " << &pn << endl;
	
	return 0;
}
