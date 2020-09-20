#include <iostream>
#include <fstream>
#include <string>

using namespace std;


int main()
{
	int row, col;
	
	ifstream my_file ("input1.txt", ios::in);

	if (my_file.is_open())
	{
		my_file >> row >> col;
	
		cout << "Row: "<< row << " " << "Coloumn: " << col << endl;
		
		my_file.close();
	}
	else cout << "Unable to open file"; 

	return 0;
}	
	
