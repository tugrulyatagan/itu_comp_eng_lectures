#include <iostream>

using namespace std;

int value(int);

int main()
{
	int n = 5;

	cout << "n nin ilk degeri: " << n << endl;
	cout << "n nin value fonksiyonu sonrasi degeri: " << value(n) << endl;

	return 0;
}

int value(int n)
{
	return n*n;
}
