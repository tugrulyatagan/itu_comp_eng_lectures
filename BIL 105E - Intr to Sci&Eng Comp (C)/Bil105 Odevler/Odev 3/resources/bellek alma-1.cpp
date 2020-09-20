#include <iostream>
#include <fstream>
#include <string>

using namespace std;


int read_file(ifstream& in_file, int &row, int &col, double *array, double **matrix)
{
    //Reads elements of a matrix from a in_file and stores the elements into one 
    // dimensional array and  two dimensional matrix parameters.  
    // row and col parameters represents the number of rows and columns of the matrix. 
}


int main(int argc, char* argv[])
{
    int row1, col1, row2, col2;
	
	ifstream in_file1;
	in_file1.open(argv[1], ios::in);				//ilk arguman myfile_1
    
    ifstream in_file2;
    in_file2.open(argv[2], ios::in);				//ikinci arguman myfile_2

	ofstream out_file;
	out_file.open(argv[3], ios::out);

	if (in_file1.is_open() && in_file2.is_open())	
	{
		in_file1 >> row1 >> col1;
		in_file2 >> row2 >> col2;		
	}
	else cout << "Unable to open files" << endl; 	//argumanlar acilamazsa uyari verir
		
	double **matrix1, **matrix2, **result;
	
	matrix1 = new double *[row1];

	for (int i = 0; i < row1; i++)
		matrix1[i] = new double [col1];
	
	//matrix1[i][j];
	
	
	//read_file(in_file1, row1, col1, array1, matrix1);	// Read the first file
	//read_file(in_file2, row2, col2, array2, matrix2);	// Read the second file
	
	
	delete[] matrix1;
	return 0;
}	
	


//myfile_1.close();
//myfile_2.close();

