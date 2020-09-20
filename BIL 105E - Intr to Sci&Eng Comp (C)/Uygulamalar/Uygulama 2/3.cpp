/***************************************************************************
* ornek   : 2-3                                                            *
* aciklama: iki kisa kenari verilen dik ucgenin hipotenusunu bulan program *    
* derleme : g++ -o program_ismi 3.cpp                                  *
***************************************************************************/

#include <iostream>
#include <cmath>

using namespace std;

	float kenar1, kenar2, hipotenus;

int main()
{

	
	cout << "Ucgenin kenarlarini giriniz: ";
	cin >> kenar1 >>kenar2;
	
	hipotenus = sqrt((kenar1 * kenar1) + (kenar2 * kenar2));
	//hipotenus = sqrt(pow(kenar1,2) + pow(kenar2,2));
	cout << "Ucgenin hipotenusu = " << hipotenus << endl;
	
	return 0;	
}
