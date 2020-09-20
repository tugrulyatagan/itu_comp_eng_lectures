#include <iostream>
#include <fstream>

using namespace std;

int main()
{
	unsigned int car;
	float miles, gallon, tmiles = 0, tgallon = 0;
	
	ifstream file;
	file.open("DATA.txt",ios::in);
	
	if (file.good())
	{
		cout << "Car" << "\t" << "MPG" << endl;
		cout << "----" << "\t" << "------" << endl;
		while (!file.eof())
		{
			file >> car >> miles >> gallon;
			
			cout << car << "\t" << miles / gallon<< endl;
			
			tmiles += miles; 
			tgallon += gallon;
		}
		
		cout << endl << "Total miles:" << tmiles << endl;
		cout << "Total gallons:" << tgallon << endl;
		cout << "Avg. miles per gallon:" << tmiles / tgallon << endl;
		
		file.close();
	}
	else
		cout << "HATA";

	return 0;
}
