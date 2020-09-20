#include <iostream>

using namespace std;

int main()
{
	int x, a , b, c;

	for (x = 100; x < 1000; x++)
	{
		a = x / 100;
		b = (x /10) % 10;
		c = x % 10;
		
		if (a < b && b < c)
			cout << x << " ";
	}
}
