#include <iostream>
#include <fstream>
#include <string>

using namespace std;


int read_file(ifstream& in_file, int &row, int &col, double *array, double **matrix)
{
	for (int i = 0; i < row * col; i++)
		in_file >> array[i];


	
	
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
			in_file >> matrix[i][j];
	}



    // Reads elements of a matrix from a in_file and stores the elements into one 
    // dimensional array and  two dimensional matrix parameters.  
    // row and col parameters represents the number of rows and columns of the matrix. 
}


void print_matrix(double **matrix, int row, int col)
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
			cout << matrix[i][j] << " ";
		cout << endl;
	}
	//Prints the elements of a matrix to the screen.  
}

void print_array(double *array, int row, int col)
{
	for (int i = 0; i < row * col; i++)
		cout << array[i] << " ";
	cout << endl;
	//Prints the elements of a matrix (matrix is represented as an array)  to the screen.
}



int main(int argc, char* argv[])
{
    int row1, col1, row2, col2;

	ifstream in_file1;
	in_file1.open(argv[1], ios::in);

    ifstream in_file2;
    in_file2.open(argv[2], ios::in);

	ofstream out_file;
	out_file.open(argv[3], ios::out);


	if (in_file1.is_open() && in_file2.is_open())	
	{
		in_file1 >> row1 >> col1;
		in_file2 >> row2 >> col2;
	}
	else cout << "Unable to open files" << endl;


	double **matrix1, **matrix2, **result;

	matrix1 = new double *[row1];
	matrix2 = new double *[row2];

	for (int i = 0; i < row1; i++)
		matrix1[i] = new double [col1];

	for (int i = 0; i < row2; i++)
		matrix2[i] = new double [col2];


    double *array1, *array2, *array_result;

	array1 = new double [row1 * col1];
	array2 = new double [row2 * col2];


	read_file(in_file1, row1, col1, array1, matrix1);
	read_file(in_file2, row2, col2, array2, matrix2);





	print_matrix(matrix1, row1, col2); 
	print_array(array1, row1, col2);






	delete[] matrix1;
	delete[] matrix2;
	delete[] array1;
	delete[] array2;

	in_file1.close();
	in_file2.close();

	return 0;
}
