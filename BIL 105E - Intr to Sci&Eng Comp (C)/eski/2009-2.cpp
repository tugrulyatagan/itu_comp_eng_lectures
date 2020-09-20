#include <iostream>
#include <math.h>

using namespace std;

int main()
{
	double N, x, y, d;
	
	cout << "Enter number: ";
	cin >> N;
	
	x = 1;

	while (1)
	{
		y = (x + (N / x)) / 2;
		
		d = fabs(y - x);
		if (d < 0.001)
			break;
			
		x = y;
	}
	cout << "Squareroot is: " << y << endl;
	
	return 0;
}
