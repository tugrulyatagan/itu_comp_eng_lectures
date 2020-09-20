#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{
    int row1, col1, row2, col2;
	
	
	
	ifstream my_file1 ("input1.txt", ios::in);
	ifstream my_file2 ("input2.txt", ios::in);

	if (my_file1.is_open() && my_file2.is_open())	//my_file1 veya my_file2 acilamazsa uyarı verir
	{
		my_file1 >> row1 >> col1;
		my_file2 >> row2 >> col2;
		

		cout << "Row1: "<< row1 << " " << "Coloumn1: " << col1 << endl; 
		cout << "Row2: "<< row2 << " " << "Coloumn2: " << col2 << endl;
	}
	else cout << "Unable to open files"; 
		
	return 0;
}	
	










//my_file1.close();
//my_file2.close();

