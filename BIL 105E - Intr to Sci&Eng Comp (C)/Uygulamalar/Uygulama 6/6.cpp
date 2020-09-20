/********************************************************
* ornek   : 5-6											*
* aciklama: cemberin cevresi ve dairenin alanini bulur	*
* derleme : g++ -o program_ismi 6.cpp						*
********************************************************/
#include <cstdio>
#include <iostream>

using namespace std;
#define PI 3.14

float cemberin_cevresi(float r, float pi)
{
	return 2*r*pi;
}

float dairenin_alani(float r)
{
	return r*r*PI;
}

int main()
{	
	float r;
	
	cout<< "Yaricapi giriniz:";
	
	cin>> r;
	cout<<"Cemberin cevresi=" <<  cemberin_cevresi(r,PI) << "\n";
	cout<<"Dairenin alaný ="<< dairenin_alani(r) <<"\n";
	
	return 0;
}
