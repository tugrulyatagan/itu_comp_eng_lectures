/********************************************************
* ornek   : 5-2											*
* aciklama: secilen dile gore kisiyi selamlayan program	*
* derleme : g++ -o program_ismi 2.cpp					*
********************************************************/

#include <cstdio>
#include <iostream>

using namespace std;

int main()
{	
	int secim;
	
	cout << "1-Turkce\n";
	cout << "2-Ingilizce\n";
	cout << "3-Fransizca\n";
	cin>> secim;
	switch (secim){
		case 1: {cout<<"Merhaba\n";	break; }
		case 2: {cout<<"Hello\n";	break; }
		case 3: {cout<<"Salut\n";	break; }
	}
	
	return 0;
}
