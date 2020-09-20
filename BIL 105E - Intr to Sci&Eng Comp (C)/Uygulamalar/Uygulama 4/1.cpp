/************************************************
* ornek   : 4-1									*
* aciklama: if ile 2 sayinin karsilastirilmasi	*
* derleme : g++ -o program_ismi 1.cpp			*
************************************************/

#include <iostream>

using namespace std;
int main()
{
	int sayi1, sayi2;
	
	cout << "2 sayi giriniz: ";
	cin >> sayi1 >> sayi2;
	
	if (sayi1 > sayi2) 
		cout << "Sayi1: " << sayi1 << " buyuktur sayi2: " << sayi2 << endl;
	else if (sayi1 < sayi2) 
		cout << "Sayi1: " << sayi1 << " kucuktur sayi2: " << sayi2 << endl;
	else 
	    cout << "Sayilar esittir" << endl;
	
	return 0;
}
