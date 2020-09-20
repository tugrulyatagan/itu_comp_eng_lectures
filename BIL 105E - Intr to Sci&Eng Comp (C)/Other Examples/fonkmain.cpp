#include <stdlib.h>
#include <iostream.h>
#include "fonk.h"

void main ( )
{
	int Sayi;

	cout << "Bir sayi girin: ";
	cin >> Sayi;
	
      cout << "Sayinin kupu:" << KupHesapla(Sayi) << endl;

      cout << "Sayinin faktoriyeli:" << Faktoriyel(Sayi) << endl << endl;

      system("PAUSE");
}
