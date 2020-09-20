/****************************************
* ornek   : 3-5							*
* aciklama: if ile 3 sayiyi siralamak	*
* derleme : g++ -o program_ismi 5.cpp   *
****************************************/

#include <iostream>

using namespace std;

int main()
{
	int a, b, c;
	
	cout << "Dizilecek 3 sayiyi ( a b c ) giriniz : ";
	cin >> a >> b >> c;
	
	if ((a > b) && (a > c))
	{
		cout << "En buyuk sayi a : " << a << endl;
		if (b > c)
		{
			cout << "Ikinci buyuk sayi b : " << b << endl;
			cout << "En kucuk sayi c : " << c << endl;
		}
		else if ( c > b)
		{ 
			cout << "Ikinci buyuk sayi c : " << c << endl;
			cout << "En kucuk sayi b : " << b << endl;
		} 
		else
			cout << "c ve b esit" << endl;
	}
	
	else if ((b > a) && (b > c))
	{
		cout << "En buyuk sayi b : " << b << endl;
		if (a > c)
		{
			cout << "Ikinci buyuk sayi a : " << a << endl;
			cout << "En kucuk sayi c : " << c << endl;
		}
		else if (c > a){ 
			cout << "Ikinci buyuk sayi c : " << c << endl;
			cout << "En kucuk sayi a : " << a << endl;
		} 
		else
			cout << "a ve c esit" << endl;
	}
		
	else if ((c > a) && (c > b))
	{
		cout << "En buyuk sayi c : " << c << endl;
		if (a > b)
		{
			cout << "Ikinci buyuk sayi a : " << a << endl;
			cout << "En kucuk sayi b : " << b << endl;
		}
		else if (b > a)
		{ 
			cout << "Ikinci buyuk sayi b : " << b << endl;
			cout << "En kucuk sayi a : " << a << endl;
		} 
		else 
			cout << "a ve b esit" << endl;
	}		
	else cout << "Hepsi esit" << endl;
	
	return 0;	
}
