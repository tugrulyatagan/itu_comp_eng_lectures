/***************************
*MATRIX MULTIPLIER         *
*Tugrul Yatagan            *
*040100117                 *
***************************/
#include <iostream>
#include <fstream>
#include <iomanip>		// for editting results

using namespace std;

void read_file(ifstream& in_file, int &row, int &col, double *array, double **matrix)
{
	for (int i = 0; i < row * col; i++)
		in_file >> array[i];			// reading from file

	in_file.seekg (3, ios::beg);		// position setting for matrix notation
	
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
			in_file >> matrix[i][j];	// readimg from file
	}
}

void write_file(ofstream& out_file, int row, int col, double **matrix)
{
	out_file << "The result matrix:" << endl << endl;
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
			out_file << setw (6) << matrix[i][j];		// writing to output file
		out_file << endl;
	}
}

void print_matrix(double **matrix, int row, int col)
{
	cout << "Matrix form of result: " << endl;
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
			cout << setw (6) << matrix[i][j];
		cout << endl;
	}
}

void print_array(double *array, int row, int col)
{
	cout << "Array form of result: " << endl;
	for (int i = 0; i < row * col; i++)
		cout << "  " << array[i];
	cout << endl;
}

void multip(double **matrix1, double **matrix2, double **result, int k, int m, int n)
{																  // r1    c1=r2   c2
	for (int a = 0; a < k; a++)				// rows
	{
		for (int b = 0; b < n; b++)			// coloumns
		{
			for (int c = 0; c < m; c++)		// multiplication elements
				result[a][b] += matrix1[a][c] * matrix2[c][b];
		}
	}
}

void multip_array(double *array1, double *array2, double *array_result, int k, int m, int n)
{																  		  //r1    c1=r2   c2
	for (int a = 0; a < k * n ; a++)
	{
		array_result[a] = 0;
		for (int b = 0; b < m; b++)			// element number
			array_result[a] += array1[b + (m * (a / n))] * array2[(b * n) + (a % n)];
	}							   			// a/n= .th row number		a%n= .th col number
}

int main(int argc, char* argv[])
{
    int row1, col1, row2, col2;

	ifstream in_file1;
	in_file1.open(argv[1], ios::in);		// first argument is first input file

    ifstream in_file2;
    in_file2.open(argv[2], ios::in);		// second argument is second input file

	ofstream out_file;
	out_file.open(argv[3], ios::out);		// third argument is output file


	if (in_file1.good() && in_file2.good())	// check input files succesfuly open
	{
		in_file1 >> row1 >> col1;			// first two elements of input is row coloumn information
		in_file2 >> row2 >> col2;
	}
	else
	{
		cout << "Unable to open input files" << endl;
		return 0;
	}
	if (!out_file.good())		// check output file is succesfuly opened
	{
		cout << "Output parameter name is needed!" << endl;
		return 0;
	}

	if (col1 != row2)
	{
		cout << "These two matrices can't be multiplied!" << endl;
		return 0;
	}


	double **matrix1, **matrix2, **result;

	matrix1 = new double *[row1];		// dynamic memory allocation for matrices
	matrix2 = new double *[row2];
	result = new double *[row1];

	for (int i = 0; i < row1; i++)
		matrix1[i] = new double [col1];
	for (int i = 0; i < row2; i++)
		matrix2[i] = new double [col2];
	for (int i = 0; i < row1; i++)
		result[i] = new double [col2];


    double *array1, *array2, *result_array;		// dynamic memory allocation according for array

	array1 = new double [row1 * col1];			// dynamic memory allocation according to array inputs and output
	array2 = new double [row2 * col2];
	result_array = new double [row1 * col2];

	read_file(in_file1, row1, col1, array1, matrix1);		// input files reads
	read_file(in_file2, row2, col2, array2, matrix2);

	multip(matrix1, matrix2, result, row1, col1, col2);		// matrices are multiplied
	multip_array(array1, array2, result_array, row1, col1, col2); // matrices are multiplied in array notation

	print_matrix(result, row1, col2);			// display result martix
	cout << endl;
	print_array(result_array, row1, col2);		// display result array

    write_file(out_file, row1, col2, result);	// writing result matrix to output file

	delete[] matrix1;	// deallocation
	delete[] matrix2;
	delete[] array1;
	delete[] array2;
	delete[] result;
	delete[] result_array;

	in_file1.close();	// closing files
	in_file2.close();
	out_file.close();

	return 0;
}
