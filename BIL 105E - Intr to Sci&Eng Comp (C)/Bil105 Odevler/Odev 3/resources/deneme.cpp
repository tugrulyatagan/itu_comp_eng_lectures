#include<iostream>
#include<fstream>
	
using namespace std;


int main()
{
	
	ifstream file_r;
	int row, col;
	file_r.open("input1.txt", ios::in);

	file_r >> row >> col;
	
	cout << "Row: "<< row << " " << "Coloumn: " << col << endl;

	
}	
	
