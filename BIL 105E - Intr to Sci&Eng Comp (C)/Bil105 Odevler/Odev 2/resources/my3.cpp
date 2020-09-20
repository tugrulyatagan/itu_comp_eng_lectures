#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cmath>
#include <iomanip>

#define ITERATION 6

using namespace std;

int getRange(long int number, int startIndex, int endIndex);
int myRand();
bool repetitionControl(int random_number1, int random_number2, int random_number3, int random_number4, int random_number5, int random_number6);




int main()
{
	char option;
	int random_number1, random_number2, random_number3, random_number4, random_number5, random_number6;
	bool exitLotto = false;
	int seed, columnCount;
	
	srand(time(0));
	
	while (!exitLotto){

	cout << "secim 1, 2, 3 yada 4  : ";
	cin >> option;
	
	switch (option) {
		
		case '0': {
			exitLotto = true;
			break;
		}


		case '1': {
			cout << "Enter column count :  ";
			cin >> columnCount;
		
			for (int n = 0; n < columnCount; n++) {
				do {
					random_number1 = 1 + myRand() % 49;
					random_number2 = 1 + myRand() % 49;
					random_number3 = 1 + myRand() % 49;
					random_number4 = 1 + myRand() % 49;
					random_number5 = 1 + myRand() % 49;
					random_number6 = 1 + myRand() % 49;
				}while(!(repetitionControl(random_number1, random_number2, random_number3, random_number4, random_number5, random_number6)));
				
				cout << "-------------------------------------" << endl;
				cout << setfill (' ') << left << setw (6);
				cout << random_number1 << setw (6) << random_number2 << setw (6) << random_number3 << setw (6) << random_number4 << setw (6) << random_number5 << setw (6) << random_number6 << endl;
			}
			cout << "-------------------------------------" << endl;
			break;
		}
				
		
		case '2': {
			int constantColumnCount, constantNumber;
			
			cout << "Enter column count :  ";
			cin >> columnCount;
		
			cout << "Enter constant number :  ";
			cin >> constantNumber;
			
			cout << "Enter constant column count :  ";
			cin >> constantColumnCount;
			
			
			for (int n = 0; n < constantColumnCount; n++) {
				
				do {
					random_number1 = constantNumber;
					random_number2 = 1 + myRand() % 49;
					random_number3 = 1 + myRand() % 49;
					random_number4 = 1 + myRand() % 49;
					random_number5 = 1 + myRand() % 49;
					random_number6 = 1 + myRand() % 49;
				}while(!(repetitionControl(random_number1, random_number2, random_number3, random_number4, random_number5, random_number6)));
				
				cout << "-------------------------------------" << endl;
				cout << setfill (' ') << left << setw (6);
				cout << random_number1 << setw (6) << random_number2 << setw (6) << random_number3 << setw (6) << random_number4 << setw (6) << random_number5 << setw (6) << random_number6 << endl;
			}
			
			for (int n = 0; n < columnCount - constantColumnCount; n++) {
				do {
					random_number1 = 1 + myRand() % 49;
					random_number2 = 1 + myRand() % 49;
					random_number3 = 1 + myRand() % 49;
					random_number4 = 1 + myRand() % 49;
					random_number5 = 1 + myRand() % 49;
					random_number6 = 1 + myRand() % 49;
				}while(!(repetitionControl(random_number1, random_number2, random_number3, random_number4, random_number5, random_number6)));
				
				cout << "-------------------------------------" << endl;
				cout << setfill (' ') << left << setw (6);
				cout << random_number1 << setw (6) << random_number2 << setw (6) << random_number3 << setw (6) << random_number4 << setw (6) << random_number5 << setw (6) << random_number6 << endl;
			}
			
			cout << "-------------------------------------" << endl;
			break;
		}
		
		
		case '3': {
			int lowerLimit, upperLimit, numberCount;
			
			cout << "Enter column count :  ";
			cin >> columnCount;
			
			cout << "Enter lowerLimit :  ";
			cin >> lowerLimit;
			lowerLimit = lowerLimit + 1;
			
			cout << "Enter upperLimit:  ";
			cin >> upperLimit;	
			
			cout << "Enter numberCount:  ";
			cin >> numberCount;					
		
		
		
			for (int n = 0; n < columnCount; n++) {
				do {
					
					random_number1 = 1 + myRand() % 49;
					random_number2 = 1 + myRand() % 49;
					random_number3 = 1 + myRand() % 49;
					random_number4 = 1 + myRand() % 49;
					random_number5 = 1 + myRand() % 49;
					random_number6 = 1 + myRand() % 49;
					
					int array[6] = {random_number1, random_number2, random_number3, random_number4, random_number5, random_number6};
					
					for(int k = 0; k < numberCount; k++) {
						array[k] = lowerLimit + myRand() % (upperLimit - lowerLimit);
					}
					
					random_number1 = array[0];
					random_number2 = array[1];
					random_number3 = array[2];
					random_number4 = array[3];
					random_number5 = array[4];
					random_number6 = array[5];
					
					

			
				}while(!(repetitionControl(random_number1, random_number2, random_number3, random_number4, random_number5, random_number6)));
				
				cout << "-------------------------------------" << endl;
				cout << setfill (' ') << left << setw (6);
				cout << random_number1 << setw (6) << random_number2 << setw (6) << random_number3 << setw (6) << random_number4 << setw (6) << random_number5 << setw (6) << random_number6 << endl;
			}
			cout << "-------------------------------------" << endl;
			break;
		}
		
		
		case '4':
		{
			int distance;

			cout << "Enter column count :  ";
			cin >> columnCount;
			
			cout << "Enter 	min. distance between numbers : ";
			cin >> distance;
			distance = distance + 1;
			
			for (int n = 0; n < columnCount; n++) {
				int swap_number1, swap_number2, swap_number3, swap_number4, swap_number5, swap_number6;
				do {

					do {
						random_number1 = 1 + myRand() % 49;
						random_number2 = 1 + myRand() % 49;
						random_number3 = 1 + myRand() % 49;
						random_number4 = 1 + myRand() % 49;
						random_number5 = 1 + myRand() % 49;
						random_number6 = 1 + myRand() % 49;
	
						int array[6] = {random_number1, random_number2, random_number3, random_number4, random_number5, random_number6};
						
	
						for(int x = 0; x < 6; x++) {
							for(int y = x+1; y < 6; y++) {
								if(array[y] < array[x]) {
									int temp = array[x];
									array[x] = array[y];
									array[y] = temp;
								}
							}	
						}					
						
						swap_number1 = array[0];
						swap_number2 = array[1];
						swap_number3 = array[2];
						swap_number4 = array[3];
						swap_number5 = array[4];
						swap_number6 = array[5];
					}while(((swap_number2 - swap_number1) < distance) || ((swap_number3 - swap_number2) < distance) || ((swap_number4 - swap_number3) < distance) || ((swap_number5 - swap_number4) < distance) || ((swap_number6 - swap_number5) < distance));
					

				}while(!(repetitionControl(random_number1, random_number2, random_number3, random_number4, random_number5, random_number6)));
				
				cout << "-------------------------------------" << endl;
				cout << setfill (' ') << left << setw (6);
				cout << random_number1 << setw (6) << random_number2 << setw (6) << random_number3 << setw (6) << random_number4 << setw (6) << random_number5 << setw (6) << random_number6 << endl;
			}
			cout << "-------------------------------------" << endl;
			break;
		}
		
	}
	}
	return 0;
}


int myRand()
{	
	seed = 1000 + rand() % 10000;
	
	for (int n = 0; n < ITERATION; n++) {
		if(seed < 1000)
			seed = seed + 1000;
			
		seed = getRange(pow(seed,2), 2, 5);
	}	

	return seed;
}	


int getRange(long int number, int startIndex, int endIndex)
{
	int result, count, digit = 0, left, right;
	count = number;
	
	while (count != 0) { 
		count /= 10; digit++; 
	}
	
	left = pow(10,(digit - startIndex + 1));
	right = pow(10,(digit - endIndex));
	
	result = (number % left) / right;
	
	return result;
}



bool repetitionControl(int random_number1, int random_number2, int random_number3, int random_number4, int random_number5, int random_number6)
{
	int array[6] = {random_number1, random_number2, random_number3, random_number4, random_number5, random_number6};
	
	for(int x = 0; x < 6; x++) {
		for(int y = x+1; y < 6; y++) {
			if(array[y] < array[x]) {
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
		
}



