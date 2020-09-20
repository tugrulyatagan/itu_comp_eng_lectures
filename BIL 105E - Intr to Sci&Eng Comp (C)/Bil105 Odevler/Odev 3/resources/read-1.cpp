#include <iostream>
#include <fstream>
#include <string>

using namespace std;


int read_file(ifstream& in_file, int &row, int &col, double *array, double **matrix)
{
	ifstream file_r;
	int oku;
	file_r.open("input1.txt", ios::in);


	cout << "Dosyanin ici: ";
	while(!file_r.eof())
	{
		file_r >> oku;
		cout << oku;
	}	
	
	cout << endl;
	
	
	
	
	
	
	
	
    //Reads elements of a matrix from a in_file and stores the elements into one dimensional array and two dimensional matrix parameters.  
    // row and col parameters represents the number of rows and columns of the matrix. 
}



int main(int argc, char* argv[])
{
    // Input and output files will be obtained from user using argv.
    int row1, col1, row2, col2;
    //row1 and col1 will be read from first line of the input file1
    //row2 and col2 will be read from first line of the input file2  
 
    // Two dimensional arrays can be defined using pointer to pointers:
     double **matrix1, **matrix2, **result;
    // Dynamic memory allocation for two dimensional arrays:
    matrix1 = new double *[row1];
    for (int i = 0; i < col1; i++)
        matrix1[i] = new double [col1];
    //You can access the elements of the two dimensional arrays using matrix notation: matrix1[i][j] or 
    // pointer arithmetic:  *(*(matrix + i) + j)

     read_file(in_file1, row1,col1,array1,matrix1); // Read the first file
     read_file(in_file2, row2,col2,array2, matrix2);  // Read the second file
     //print out the result matrix
     print_matrix(result, row1, col2); 
     // print out the result array 
     print_array(result_array, row1, col2);

    return 0;
}
