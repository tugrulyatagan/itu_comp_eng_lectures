#include <iostream>
#include <math.h>

using namespace std;

int main()
{
	long double a, b, w, x, sum;
	unsigned long int n;
	
	cout << "Insert a and b: " << endl;
	cin >> a >> b;
	cout << "Insert n: " << endl;
	cin >> n;
	
	w = (b - a) / n;
	
	for (x = a; x < b; x += w)
	{
		sum = sum + w * sqrt(4 - pow(x,2));
	}
	
	cout << sum;
	return 0;
}
