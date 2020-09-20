/************************************************************************
*																		*
* 																		*
* fonksiyon call by value / call by reference ornegi 1					*
* derlemek icin g++ -o program_ismi 1.cpp									*
*																		*
************************************************************************/

#include <iostream>

using namespace std;
int value(int);

int main()
{
	int n = 5;
	
	cout <<"n'nin ilk degeri: "<< n<< "\n";
	cout<< "n'nin value fonksiyonu sonrasi degeri:"<< value(n);
   
    	return 0;
}

int value(int n)
{
	return n*n;
   
}
