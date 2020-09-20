#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;

int main(int argc, char* argv[])
{
    int row1, col1, row2, col2;
	
	ifstream myfile_1;
	myfile_1.open(argv[1], ios::in);				//ilk arguman myfile_1
    
    ifstream myfile_2;
    myfile_2.open(argv[2], ios::in);				//ikinci arguman myfile_2

	if (myfile_1.is_open() && myfile_2.is_open())	
	{
		myfile_1 >> row1 >> col1;
		myfile_2 >> row2 >> col2;		
	}
	else cout << "Unable to open files" << endl; 	//argumanlar acilamazsa uyari verir
		
	double **matrix1, **matrix2, **result;
	
	
	
	
	
	matrix1 = new double *[row1];

	for (int i = 0; i < row1; i++)
		matrix1[i] = new double [col1];
	
	
	
			
	return 0;
}	
	


//myfile_1.close();
//myfile_2.close();

