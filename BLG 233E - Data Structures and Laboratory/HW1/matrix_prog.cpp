/********************************************
* BLG 233E DATA STRUCTURES AND LABORATORY	*
* CRN: 11146								*
* HOMEWORK 1								*
* MATRIX	CALCULATOR						*
* TUGRUL YATAGAN							*
* 040100117									*
********************************************/
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include "linked_list.h"
using namespace std;

void generate_matrices(); // matrisleri olusturacak methodlari cagirir
void take_dimensions(); // kullanicidan ve girdi matristen matrislerin buyukluk bilgisi alinir
void print_menu(); // menuyu ekrana yazdirir
void choose_operations(char); // kullanicinin sectigi islemdeki fonksiyonu cagirir
void multiply_matrices();
void find_transposes();
void check_symmetry();
void check_zero();
void calculate_determinant();

LinkedList matrix1, matrix2; // matrix1 ve matrix2 adinda iki tane LinkedList yapisi acilir

int main(){
	cout << "BLG 233E Data Str/uctures and Laboratory" << endl;
	cout << "Assignment #1" << endl;
	cout << "040100117" << endl;
	cout << "TUGRUL YATAGAN" << endl;
	cout << endl;

	generate_matrices(); // matrisler olusturulur

	char terminate, choice;
	while(1){
		print_menu();
		cin >> choice;
		choose_operations(choice);
		cout << "Do you want to continue the program? {(y) or (n)} : ";
		cin >> terminate;
		if(terminate == 'n' || terminate == 'N')
			break; // program dongusu sonlandirilir
	}
	matrix1.clear(); // cikista matrisler bellege geri iade edilir
	matrix2.clear();
	return EXIT_SUCCESS;
}

void generate_matrices(){
	matrix1.create(); //  bos bagli liste olusturulur
	matrix2.create(); // bos bagli liste olusturulur

	take_dimensions(); // matrislerin boyutu alinir
	srand(100 + time(0)*time(0)*time(0) % 10 ); // srand a rastgele tohum verilir

	matrix1.generaterand(); // rastgele matris olusturulur
	matrix2.readfile(); // girdi matrisi okunur

	cout << endl << "First matrix : " << endl;
	matrix1.print(); // matrisler ekrana yazdirilir
	cout << endl << "Second matrix : " << endl;
	matrix2.print();
	cout << endl ;
}

void take_dimensions(){
	ifstream input_matrix;
	input_matrix.open("matrix.txt", ios::in);
	if(input_matrix.good()){
		input_matrix >> matrix2.row >> matrix2.col; // girdideki ilk iki sayi ile matrisin boyutlari alinir
	}
	else
		cerr << "MATRIX FILE CAN NOT BE OPENED!" << endl << endl;
	cout << "Please insert the dimension of the first matrix" << endl;
	cout << "Row number: ";
	cin >> matrix1.row ; // kullanicidan matrisin boyut bilgileri alinir
	if(cin.fail()){
		cin.clear(); // yanlis girdiyi temizler 
		cin.ignore(10000,'\n'); // 1000 integer olmayan girdiyi reddeder
		cout << "Please insert only integer number!" << endl;
	}
	cout << "Coloumn number: ";
	cin >> matrix1.col;
	if(cin.fail()){
		cin.clear(); // yanlis girdiyi temizler 
		cin.ignore(10000,'\n'); // 1000 integer olmayan girdiyi reddeder
		cout << "Please insert only integer number!" << endl;
	}
}

void print_menu(){
	cout << endl;
	cout << "MATRIX APPLICATION" << endl;
	cout << "Choose an operation" << endl;
	cout << "M: Multiply the matrices" << endl;
	cout << "T: Find transpose of the matrices" << endl;
	cout << "S: Check the matrices symmetric or not " << endl;
	cout << "Z: Check the matrices zero matrix or no" << endl;
	cout << "D: Calculate the determinant of the matrices" << endl;
	cout << endl;
	cout << "Enter an option {M, T, S, Z, D} : ";
}

void choose_operations(char choice){
	switch (choice){
	case 'M': case 'm':
		multiply_matrices();
		break;
	case 'T': case 't':
		find_transposes();
		break;
	case 'S': case 's':
		check_symmetry();
		break;
	case 'Z': case 'z':
		check_zero();
		break;
	case 'D': case 'd':
		calculate_determinant();
		break;
	default:
		cout << "Error: You have made an invalid choice" << endl;
		cout << "Try again {M, T, S, Z, D} : ";
		cin >> choice; // kullanicidan secenek alinir
		choose_operations(choice);
		break;
	}
}

void multiply_matrices(){
	if(matrix1.col != matrix2.row){ // matrislerin carpilabilme durumu kontrol edilir
		cerr << "These two matrices cannot be multiplied!" << endl;
	}
	else{
		cout << "Multiplication matrix = " << endl;
		multiply();
	}
}

void find_transposes(){
	cout << "Transpose of the first matrix = " << endl;
	matrix1.transpose();
	cout << "Transpose of the second matrix = " << endl;
	matrix2.transpose();
}

void check_symmetry(){
	if(matrix1.col != matrix1.row){ // matrisin kare matris olup olmadigi kontrol edilir
		cout << "First matrix is not a square matrix so it is not a symmetric matrix" << endl;
	}
	else{
		if(matrix1.symmetry() == 1)
			cout << "First matrix is a symmetric matrix" << endl;
		else
			cout << "First matrix is not a symmetric matrix" << endl;
	}
	if(matrix2.col != matrix2.row){
		cout << "Second matrix is not a square matrix" << endl;
	}
	else{
		if(matrix2.symmetry() == 1)
			cout << "Second matrix is a symmetric matrix" << endl;
		else
			cout << "Second matrix is not a symmetric matrix" << endl;
	}
}

void check_zero(){
	if(matrix1.zero() == 1)
		cout << "First matrix is a zero matrix" << endl;
	else
		cout << "First matrix is not a zero matrix" << endl;
	if(matrix2.zero() == 1)
		cout << "Second matrix is a zero matrix" << endl;
	else
		cout << "Second matrix is not a zero matrix" << endl;
}

void calculate_determinant(){
	if((matrix1.row == 3) && (matrix1.col == 3)) // matrisin 3x3 matris olup olmadigi kontrol edilir
		cout << "Determinant of the first matrix = " << matrix1.determinant() << endl;
	else
		cout << "First matrix is not a 3x3 matrix" << endl;
	if((matrix2.row == 3) && (matrix2.col == 3))
		cout << "Determinant of the second matrix = " << matrix2.determinant() << endl;
	else
		cout << "Second matrix is not a 3x3 matrix" << endl;
}
