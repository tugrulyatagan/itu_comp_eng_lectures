/*************************************************
* ornek   : 2-c                                  *
* aciklama: kucuk harfi buyuk harf yapan program *
* derleme : g++ -o program_ismi c.cpp            *
*************************************************/

#include <iostream>

using namespace std;

int main()
{
	char c;
	char d;
	cout << "Bir harf giriniz : "; 
	cin>> c;
	//c = cin.get();
	d=cin.get();
	cout << "Girilen harf '" << c << "', buyuk hali '" << static_cast<char>(c - 32)<<"'\n";
	
	return 0;
}
