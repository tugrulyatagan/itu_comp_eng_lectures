#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cmath>
#include <iomanip>

#define ITERATION 5

using namespace std;

int getRange(long int number, int startIndex, int endIndex);
int myRand();
int control(int random_number1, int random_number2, int random_number3, int random_number4, int random_number5, int random_number6);


int seed;
int columnCount;

int main()
{
	cout << "Enter column count : ";
	cin >> columnCount;

	for (int n = 0; n < columnCount; n++)
	{
		int random_number1, random_number2, random_number3, random_number4, random_number5, random_number6;
		
		do{
			random_number1 = 1 + myRand() % 50;
			random_number2 = 1 + myRand() % 50;
			random_number3 = 1 + myRand() % 50;
			random_number4 = 1 + myRand() % 50;
			random_number5 = 1 + myRand() % 50;
			random_number6 = 1 + myRand() % 50;
		}while(!(control(random_number1, random_number2, random_number3, random_number4, random_number5, random_number6)));
		
		cout << "-------------------------------------" << endl;
		cout << setfill (' ') << left << setw (6);
		cout << random_number1 << setw (6) << random_number2 << setw (6) << random_number3 << setw (6) << random_number4 << setw (6) << random_number5 << setw (6) << random_number6 << endl;
	}
	cout << "-------------------------------------" << endl;
}













int myRand()
{	
	srand(time(0) + seed); 
	seed = (1000 + rand()) % 10000;
	
	for (int n = 0; n < ITERATION; n++)
	{
		if(seed < 1000)
			seed+=1000;
			
		seed = getRange(pow(seed,2), 2, 5);
	}	
	return seed;
}	


int getRange(long int number, int startIndex, int endIndex)
{
	int result, count, digit = 0, left, right;
	count = number;
	
	while (count != 0) 
	{ 
		count /= 10; digit++; 
	}
	
	left = pow(10,(digit - startIndex + 1));
	right = pow(10,(digit - endIndex));
	
	result = (number % left) / right;
	
	return result;
}



int control(int random_number1, int random_number2, int random_number3, int random_number4, int random_number5, int random_number6)
{
	int array[6] = {random_number1, random_number2, random_number3, random_number4, random_number5, random_number6};
	
	for(int x = 0; x < 6; x ++) 
	{
		for(int y = x+1; y < 6; y ++) 
		{
			if(array[y] < array[x]) 
			{
				int temp = array[x];
				array[x] = array[y];
				array[y] = temp;
			}
		}	
	}
	
	if (array[1] == array[2] || array[2] == array[3] || array[3] == array[4] || array[4] == array[5] || array[5] == array[6])
		return 0;
	else
		return 1;
		
	/*
	if(random_number1 == random_number2 || random_number1 == random_number3 || random_number1 == random_number4 || random_number1 == random_number5 || random_number1 == random_number6)
		return 0;
	else if(random_number2 == random_number3 || random_number2 == random_number4 || random_number2 == random_number5 || random_number2 == random_number6)
		return 0;
	else if(random_number3 == random_number4 || random_number3 == random_number5 || random_number3 == random_number6)
		return 0;
	else if(random_number4 == random_number5 || random_number4 == random_number6)
		return 0;
	else if(random_number5 == random_number6)
		return 0;
	else 
		return 1;
	*/
	
}



