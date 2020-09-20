#include <iostream>
#include <cstdio>

using namespace std;

int main()
{
	int kenar_sayisi;

	cout << "Sekilin kenar sayisini giriniz: ";

	cin >> kenar_sayisi;
	
	switch (kenar_sayisi)
	{
		case 0: { cout << "Hatali giris!" << endl; break;}
		case 3: { cout << "Ucgen" << endl; break;}
		case 4: { cout << "Dortgen" << endl; break;}
		case 5: { cout << "Besgen" << endl; break;}
		case 6: { cout << "Altigen" << endl; break;}
		default: { cout << "Cokgen" << endl;}
	}

	return 0;
}


