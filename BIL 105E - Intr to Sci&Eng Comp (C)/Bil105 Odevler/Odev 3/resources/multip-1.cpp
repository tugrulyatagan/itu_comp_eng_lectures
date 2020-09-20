#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

int read_file(ifstream& in_file, int &row, int &col, double *array, double **matrix)
{
	for (int i = 0; i < row * col; i++)
		in_file >> array[i];

	in_file.seekg (3, ios::beg);
	
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
			in_file >> matrix[i][j];
	}
}

void print_matrix(double **matrix, int row, int col)
{
	cout << "Matrix form of result: " << endl;
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			cout << setfill (' ') << right << setw (5);
			cout << matrix[i][j] << setw (5);
		}
		cout << endl;
	}
}

void print_array(double *array, int row, int col)
{
	cout << "Array form of result: " << endl;
	for (int i = 0; i < row * col; i++)
		cout << array[i] << " ";
	cout << endl;
}

void multip(double **matrix1, double **matrix2, double **result, int k, int m, int n)
{																   //r1    c1=r2   c2
	for (int a = 0; a < k; a++)
	{	
		for (int b = 0; b < n; b++)
		{	
			result[a][b] = 0; 
			for (int c = 0; c < m; c++)
			{	
				result[a][b] += matrix1[a][c] * matrix2[c][b];
			}
		}	
	}
}

void multip_array(double *array1, double *array2, double *array_result, int k, int m, int n)
{
    //multiplies one dimensional arrays array1(size: 1x(kxm)) and array2 (size: 1x(mxn)) by using   
    //pointer arithmetic and stores the results at one dimensional array array_result (size: 1x(kxn)).
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
	result = new double *[row1];

	for (int i = 0; i < row1; i++)
		matrix1[i] = new double [col1];
	for (int i = 0; i < row2; i++)
		matrix2[i] = new double [col2];
	for (int i = 0; i < row1; i++)
		result[i] = new double [col2];


    double *array1, *array2, *result_array;

	array1 = new double [row1 * col1];
	array2 = new double [row2 * col2];
	result_array = new double [row1 * col2];

	read_file(in_file1, row1, col1, array1, matrix1);
	read_file(in_file2, row2, col2, array2, matrix2);

	multip(matrix1, matrix2, result, row1, col1, col2);
	//multip_array(array1, array2, result_array, row1, col1, col2); 
	
	print_matrix(result, row1, col2); 
	//print_array(result_array, row1, col2);


	delete[] matrix1;
	delete[] matrix2;
	delete[] array1;
	delete[] array2;
	delete[] result;
	delete[] result_array;

	in_file1.close();
	in_file2.close();

	return 0;
}
