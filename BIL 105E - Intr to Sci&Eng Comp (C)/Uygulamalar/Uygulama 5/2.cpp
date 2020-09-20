/************************************************************************
*																		*
* 																		*
* fonksiyon call by value / call by reference ornegi 2					*
* derlemek icin g++ -o program_ismi 2.cpp								*
*																		*
************************************************************************/
#include <iostream>

using namespace std;

void reference(int *);

int main()
{
	int n = 5;
	
	cout<< "n'nin ilk degeri:"<< n<< "\n";
	cout<< "n'nin adresi:" << &n << "\n";
	reference(&n); //address of n	
	cout<< "n'nin reference fonksiyonu sonrasi degeri:"<<n<<"\n";	
	cout<< "n'nin adresi:" << &n << "\n";
	
	return 0;
}

void reference(int *n)
{	
	*n = *n * *n;
}
