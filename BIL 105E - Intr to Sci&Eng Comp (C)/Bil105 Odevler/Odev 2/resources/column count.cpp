#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cmath>


using namespace std;

int main()
{
	cout << "Enter column count : ";
	cin >> columnCount;
	
	for (int n=0; n < columnCount; n++)
	{
		random_number1 = 1 + myRand() % 49;
		random_number2 = 1 + myRand() % 49;
		random_number3 = 1 + myRand() % 49;
		random_number4 = 1 + myRand() % 49;
		random_number5 = 1 + myRand() % 49;
		random_number6 = 1 + myRand() % 49;
		
		cout << "------------------------------------------------------------" << endl
		 << random_number1 << random_number2 << random_number3 << random_number4 << random_number5 << random_number6
	}
	
	
}

