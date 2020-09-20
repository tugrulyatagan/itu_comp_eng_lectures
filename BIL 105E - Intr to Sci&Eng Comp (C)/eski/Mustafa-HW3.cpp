#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void print_matrix(double **matrix, int row, int col)
{
	cout << "As an matrix: " << endl;
	for(int j=0;j<row;j++)
	{		
		cout << "|\t";
		for(int k=0;k<col;k++)
		{
			cout << *(*(matrix+j)+k) << "\t";
		}
		cout << "|" << endl << "|";
		for(int l=0;l<(col+1);l++) { cout << "\t";}
		cout << "|" << endl;
	}	
	cout << endl;
}
void print_array(double *array, int row, int col)
{
	cout << "As an array = [ ";
	for(int l=0;l<row*col;l++)
	{
		cout << *(array+l) << "  ";
	}
	cout << " ]" << endl << endl;
}
void multip(double **matrix1, double **matrix2, double **result, int k, int m, int n)
{
	for(int i=0;i<k;i++)
	{
		for(int j=0;j<n;j++)
		{
			double sum=0;
			for(int a=0;a<m;a++)
			{
				sum += (*(*(matrix1+i)+a))*(*(*(matrix2+a)+j));
			}			
			*(*(result+i)+j) = sum;
		}
	}	
}
void multip_array(double *array1, double *array2, double *array_result, int k, int m, int n)
{
	for(int a=0;a<(k*n);a++)
	{
		double sum = 0;
		for(int b=0;b<m;b++)
		{	
			int row_count = a/n;
			int column_count = a%n;
			sum = sum +	array1[row_count*m+b]*array2[column_count+b*n];				
		}
		array_result[a] = sum;		
	}	
}
void read_file(ifstream& in_file, int row,int col,double *array,double **matrix)
{
	
	for(int i=0;i<row;i++)
	{
		for(int j=0;j<col;j++)
		{
			in_file >> matrix[i][j];
			array[i*col+j] =matrix[i][j];
		}
	}	
	
	
	
	
}
void write_file(ofstream& out_file, int row, int col, double **matrix)
{
	out_file << "The result matrix is:" << endl;
	out_file << "Number of rows: " << row << "\tNumber of columns: " << col << "\n\n";
	for(int i=0;i<row;i++)
	{
		out_file << "| \t";
		for(int j=0;j<col;j++)
		{
			out_file << *(*(matrix+i)+j) << "\t";
		}
		out_file << "| \n";
		out_file << "|";
		for (int k=0;k<(col+1);k++) { out_file << "\t"; }
		out_file << "|" << endl;
	}
}
int main (int argc, char* argv[]) 
{
	
	int row1,col1,row2,col2;
	
	ifstream in_file1;
	in_file1.open(argv[1], ios::in);

    ifstream in_file2;
    in_file2.open(argv[2], ios::in);

	ofstream out_file;
	out_file.open(argv[3], ios::out);
	
	
	in_file1.is_open();
	in_file1 >> row1 >> col1;
		
	
	double *array1 = new double[row1*col1];	
	double **matrix1 = new double*[row1];
	for(int i=0;i<col1;i++)
	{
		matrix1[i] = new double[col1];
	}		
	
	double *array2 = new double[row2*col2];
	double **matrix2 = new double*[row2];
	for(int i=0;i<col2;i++)
	{
		matrix2[i] = new double[col2];
	}		
	
	double *array_result = new double[row1*col2];
	double **result = new double*[row1];
	for(int i=0;i<col2;i++)
	{
		result[i] = new double[col2];
	}	
	
	read_file(in_file1,row1,col1,array1,matrix1);
	cout << "First matrix as one and two dimensional array: \n\n";
	print_matrix(matrix1,row1,col1);
	print_array(array1,row1,col1);
	
	
	in_file2.is_open();
	in_file2 >> row2 >> col2;	
	
	
	read_file(in_file2,row2,col2,array2,matrix2);
	cout << "Second matrix as one and two dimensional array: \n\n";
	print_matrix(matrix2,row2,col2);
	print_array(array2,row2,col2);
	
	
	
	multip(matrix1,matrix2,result,row1,col1,col2);
	multip_array(array1,array2,array_result,row1,col1,col2);
	
	cout << "Result matrix as one and two dimensional array: \n\n";
	print_matrix(result,row1,col2);
	print_array(array_result,row1,col2);
	
	in_file1.close();	
	in_file2.close();
	
	write_file(out_file,row1,col2,result);
	cout << "Result matrix is writen to file. \n";
	
	delete[] matrix1;
	delete[] matrix2;
	delete[] array1;
	delete[] array2;
	delete[] result;
	delete[] array_result;
	
	out_file.close();
	
	
	return 0;
}
