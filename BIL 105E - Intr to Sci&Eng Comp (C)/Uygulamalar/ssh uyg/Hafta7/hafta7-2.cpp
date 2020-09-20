#include <iostream>

using namespace std;

void referance(int *);

int main()
{
	int n = 5;

	cout << "n nin ilk degeri: " << n << endl;
	referance(&n);
	cout << "n nin referance fonksiyonu sonrasi degeri: " << n << endl;

	return 0;
}

void referance(int *n)
{
	*n = *n * *n;
}
