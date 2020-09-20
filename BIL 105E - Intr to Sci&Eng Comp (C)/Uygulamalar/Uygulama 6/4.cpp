/********************************************************
* ornek   : 5-4											*
* aciklama: kenar sayisina gore cokgenin ismini verir	*
* derleme : g++ -o program_ismi 4.cpp						*
********************************************************/

#include <cstdio>
#include <iostream>

using namespace std;

int main()
{
	int kenar_sayisi;
	
	cout << "Sekilin kenar sayisini giriniz:";
	
	cin >> kenar_sayisi;
	switch (kenar_sayisi){
		case 0: { cout<<"Hatali giris!\n";	break; }
		case 3: { cout<<"Ucgen\n"; 			break; }
		case 4: { cout<<"Dortgen\n"; 		break; }
		case 5: { cout<<"Besgen\n"; 		break; }
		case 6: { cout<<"Altigen\n"; 		break; }
		default : cout<<"Cokgen\n";
	}
	
	return 0;
}

