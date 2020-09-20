/************************************************************
* ornek   : 4-6												*
* aciklama: dik ucgenin hipotenusunu bulan program			*
* derleme : g++ -lm -o program_ismi 6.cpp					*
************************************************************/

#include <cmath>
#include <iostream>
#include <iomanip>

using namespace std;
int main(){
	
	int a, b;
	
	for (;;)
	{
		cout <<"iki kenari giriniz: ";
		cin >> a >> b;
	
		if (a > 0 && b > 0) 
		{
			cout << "sonuc: " << fixed << setprecision(2) << pow(a*a+b*b, 0.5) << endl;
			break;
		}
		else
			cout << "farkli degerler giriniz..." << endl;
	}
	
	return 0;
}

