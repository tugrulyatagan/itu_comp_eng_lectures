#include <iostream>

using namespace std;

int main()
{
	int i, dizi[10];

	for (i = 0; i < 10; i++)
	{
		dizi[i] = 0;
	}

	for (i = 0; i < 10; i++)
	{
		cout << "dizi [" << i << "] = " << dizi[i] << endl;
	}

	return 0;
}

