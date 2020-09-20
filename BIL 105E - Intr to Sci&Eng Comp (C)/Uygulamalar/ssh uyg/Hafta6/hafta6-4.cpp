#include <cstdio>
#include <iostream>

using namespace std;

#define PI 3.14

void cemberin_cevresi(float r, float pi)
{
	float cevre;
	cevre=2*pi*r;
	cout << "Cevre= " << cevre << endl;
}

float dairenin_alani(float r)
{
	return r*r*PI;
}

int main()
{
	float r;

	cout << "Yaricapi giriniz: ";

	cin >> r;
	cemberin_cevresi(r,PI);
	cout << "Dairenin alani = " << dairenin_alani(r) << endl;
return 0;
}

