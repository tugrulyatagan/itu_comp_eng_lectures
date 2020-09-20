#include <iostream>

using namespace std;

int fib(int sayi)
{
	if(sayi == 1 || sayi == 0)
		return sayi;
	else
		return (fib(sayi - 1) + fib(sayi -2));
}



int main()
{
	int sayi;

	cout << "Kacinci Fibonacci sayisi: ";
	cin >> sayi;

	cout << sayi << ". Fibomacci sayisi = " << fib(sayi) << endl;

	return 0;
}

