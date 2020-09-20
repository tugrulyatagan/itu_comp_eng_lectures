#include <iostream>
#include <cmath>
#include <cstdlib>


using namespace std;


int main()
{
	int number count, result, digit = 0, startIndex, endIndex, left, right;
	
	
	cout << "sayi gir: ";
	cin >> number;
	
	cout << "baş-son gir; ";
	cin >> startIndex >> endIndex;
	
	count = number;
	
	while (count != 0) 
	{ 
		count /= 10; digit++; 
	}
	
	left = pow(10,(digit - startIndex + 1));
	right = pow(10,(digit - endIndex));
	
	result = (number % left) / right;
	
	cout << result;
}

