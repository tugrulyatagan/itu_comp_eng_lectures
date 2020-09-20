/********************************************
* BLG 233E DATA STRUCTURES AND LABORATORY	*
* CRN: 11146								*
* HOMEWORK 1								*
* MATRIX	CALCULATOR						*
* TUGRUL YATAGAN							*
* 040100117									*
********************************************/
#include <iostream>
#include <fstream>
#include <cstdlib>
#include "linked_list.h"
using namespace std;

extern LinkedList matrix1, matrix2; //matrix_prog da tanýmlanan LinkedList tipindeki
									//matrix1 ve matrix2 deðiþkenleri aynen kullanilmak uzere alinir

void LinkedList::create(){
	head = NULL; // bos bagli liste olusturulur
}

int randomnum(){
	int random_number;
	random_number = rand() % 10; // 0-9 arasi rastgele sayi uretir
	return random_number;
}

void LinkedList::generaterand(){
	Node *first = NULL; // bagli listenin ilk elemani icin kullanilir
	Node *parent = NULL, *child = NULL; // alta bagli dugumler ve bagli olmayan dugumler icin yeni dugumler olusturulur
	for(int i=0;i<row;i++){ // bu dongu icinde satirlar olusturulur
		head = NULL;
		for(int j=0;j<col;j++){ // bu dongu icinde elemanlar olusturulur
			Node *newnode;
			newnode = new Node; // yeni dugum olusturulur
			newnode->value = randomnum(); // yeni matris elemanina rastgele deger atanir
			newnode->right = NULL; 
			newnode->down = NULL;
			if(head == NULL){ // ilk dugum kontrolu
				head = newnode;
				if(first == NULL)
					first = head;
			}
			else
				child->right = newnode; // yeni dugum baglanir
			if(parent != NULL){
				parent->down = newnode; // ustteki dugumle baglanti kurulur
				parent = parent->right; // yandaki dugumle baglanti kurulur
			}
			child = newnode;
		}
		parent = head;
	}
	// ilk haliyle head icinde right biligisi olmasýna ragmen down bilgisi yoktur
	head = first; // gecerli head olusturulur
}

void LinkedList::readfile(){
	Node *first = NULL; // bagli listenin ilk elemani icin kullanilir
	ifstream input_matrix; // dosya islemleri yapmak uzere input_matrix olusturulur 
	input_matrix.open("matrix.txt", ios::in); // "matrix.txt" okuma yapmak icin acilir
	input_matrix.seekg (3, ios::beg); // okuyucunun konumu matrisin basina ayarlanir
	Node *parent = NULL, *child = NULL; // alta bagli dugumler ve bagli olmayan dugumler icin yeni dugumler olusturulur
	for(int i=0;i<row;i++){ // satirlar sirayla okunur
		head = NULL;
		for(int j=0;j<col;j++){ // satir icindeki elemanlar sirayla okunur
			Node *newnode;
			newnode = new Node; // yeni dugum olusturulur
			input_matrix >> newnode->value; // girdi matrisin elamanlari bagli listeye aktarilir
			newnode->right = NULL;
			newnode->down = NULL;
			if(head == NULL){ // ilk dugum kontrolu
				head = newnode;
				if(first == NULL)
					first = head;
			}
			else
				child->right = newnode; // yeni dugum baglanir
			if(parent != NULL){
				parent->down = newnode; // ustteki dugumle baglanti kurulur 
				parent = parent->right; // yandaki dugumle baglanti kurulur
			}
			child = newnode;
		}
		parent = head;
	}
	// ilk haliyle head icinde right biligisi olmasýna ragmen down bilgisi yoktur
	head = first; // gecerli head olusturulur
}

int LinkedList::scanright(int nodecount){ // elemanin numarasini alir degerini doner
	// scanright matrisi saga dogru sirayla tarar satir sonunda alt satira iner
	// 1 2 3
	// 4 5 6
	// 7 8 9
	int value;
	Node *traverse_down = head; // first
	for(int i=0;i<(nodecount/col)+1;i++){ // +1 i=0 dan basladigi icin
		Node *traverse_right = traverse_down; // satir basýnda atama
		for(int j=0;j<(nodecount%col)+1;j++){
			value = traverse_right->value; // elemanin degeri okunur
			traverse_right = traverse_right->right; // yandaki elemana gecer
		}
		traverse_down = traverse_down->down; // satir sonuna gelindiginde alt asatira gecer
	}
	return value;
}

int LinkedList::scandown(int nodecount){ // elemanin numarasini alir degerini doner
	// scandown matrisi asagi dogru sirayla tarar sutun sonunda sagdaki sutuna gecer
	// 1 4 7
	// 2 5 8
	// 3 6 9
	int value;
	Node *traverse_right = head;
	for(int i=0;i<(nodecount/row)+1;i++){ // +1 i=0 dan basladigi icin
		Node *traverse_down = traverse_right; // sutun basýnda atama
		for(int j=0;j<(nodecount%row)+1;j++){
			value = traverse_down->value; // elemanin degeri okunur
			traverse_down = traverse_down->down; // alttaki elemana gecer
		}
		traverse_right = traverse_right->right; // sutun sonuna gelindiginde yan sutuna gecer
	}
	return value;
}

void LinkedList::print(){
	int count = 0;
	for(int r=0;r<row;r++){ // satir icin
		for(int c=0;c<col;c++){ // sutun icin
			cout << scanright(count++) << " "; // matrisi saga dogru tarayarak yazdirir
		}
		cout << endl;
	}
}

void multiply(){
	LinkedList result; // sonuc icin bagli liste olsuturulur
	result.create();
	result.row = matrix1.row;
	result.col = matrix2.col;
	Node *parent = NULL, *child = NULL; // alta bagli dugumler ve bagli olmayan dugumler icin yeni dugumler olusturulur
	Node *first = NULL; // bagli listenin ilk elemani icin kullanilir
	for(int r=0;r<result.row;r++){ // sonucun satirlarini olusturur
		result.head = NULL;
		for(int c=0;c<result.col;c++){ // sonucun elemanlarini olsuturur
			Node *newnode;
			newnode = new Node; // yeni dugum olusturulur
			int sum=0;
			for (int e=0;e<matrix1.col;e++) // carpim islemi icin her bir elemanin degeri hesaplanir
				sum += matrix1.scanright(r*matrix1.col+e)*matrix2.scandown(c*matrix1.col+e); // carpma islemindeki toplamalar yapilir
			newnode->value = sum; // elemanin sonucu atanir
			newnode->right = NULL;
			newnode->down = NULL;
			if(result.head == NULL){ // ilk dugum kontrolu
				result.head = newnode;
				if(first == NULL)
					first = result.head;
			}
			else
				child->right = newnode; // yeni dugum baglanir
			if(parent != NULL){
				parent->down = newnode; // ustteki dugumle baglanti kurulur
				parent = parent->right; // yandaki dugumle baglanti kurulur
			}
			child = newnode;
		}
		parent = result.head;
	}
	// ilk haliyle head icinde right biligisi olmasýna ragmen down bilgisi yoktur
	result.head = first; // gecerli head olusturulur
	result.print(); // sonuc ekrana yazdirilir
	result.clear(); // sonuc bellege iade edilir
}

void LinkedList::transpose(){
	LinkedList result; // sonuc icin bagli liste olsuturulur
	result.create();
	result.row = col;
	result.col = row;
	int nodecount=0;
	Node *parent = NULL, *child = NULL; // alta bagli dugumler ve bagli olmayan dugumler icin yeni dugumler olusturulur
	Node *first = NULL; // bagli listenin ilk elemani icin kullanilir
	for(int i=0;i<result.row;i++){ // bu dongu icinde satirlar olusturulur
		result.head = NULL;
		for(int j=0;j<result.col;j++){ // bu dongu icinde elemanlar olusturulur
			Node *newnode;
			newnode = new Node; // yeni dugum olusturulur
			newnode->value = scandown(nodecount++);
			newnode->right = NULL;
			newnode->down = NULL;
			if(result.head == NULL){ // ilk dugum kontrolu
				result.head = newnode;
				if(first == NULL)
					first = result.head;
			}
			else
				child->right = newnode; // yeni dugum baglanir
			if(parent != NULL){
				parent->down = newnode; // ustteki dugumle baglanti kurulur
				parent = parent->down; // yandaki dugumle baglanti kurulur
			}
			child = newnode;
		}
		parent = result.head;
	}
	// ilk haliyle head icinde right biligisi olmasýna ragmen down bilgisi yoktur
	result.head = first; // gecerli head olusturulur
	result.print(); // sonuc ekrana yazdirilir
	result.clear(); // sonuc bellege iade edilir
}

bool LinkedList::symmetry(){
	for(int count=0;count<row*col;count++){
		if(scanright(count) != scandown(count)) // matrisin elemanlari yatay ve duseydeki esitlikleri kontrol edilir
			return 0; // simetrik degilse 0
	}
	return 1; // simetrik ise 1
}

bool LinkedList::zero(){
	for(int i=0;i<row*col;i++){
		if(scanright(i) != 0) // matrisin tum elemanlari saga taramayla kontrol edilir
			return 0; // sifir matris degil ise 0
	}
	return 1; // sifir matris ise 1
}

int LinkedList::determinant(){
	// Sarrus kurali geregi
	// 1 2 3
	// 4 5 6
	// 7 8 9
	// Matrisinin determinanti=
	// [(1*5*9)+(4*8*3)+(7*2*6)]-[(3*5*7)+(6*8*1)+(9*2*4)]
	int result;
	result = scanright(0)*scanright(4)*scanright(8);
	result += scanright(3)*scanright(7)*scanright(2);
	result += scanright(6)*scanright(1)*scanright(5);
	result -= scanright(2)*scanright(4)*scanright(6);
	result -= scanright(5)*scanright(7)*scanright(0);
	result -= scanright(8)*scanright(1)*scanright(3);
	return result;
}

void LinkedList::clear(){
	Node *traverse_down = head; // head den bagli listenin yeri alinir
	for(int i=0;i<row;i++){
		for(int k=1;k<row-i;k++)
			traverse_down = traverse_down->down; // traverse_down her zaman ilk once en alt satira gelir
		Node *traverse_right = traverse_down; // silme islemi en alt satirdan baslar
		for(int j=0;j<col;j++){
			Node *del_right = traverse_right; // silmek icin del_right 
			traverse_right = traverse_right->right;
			delete del_right; // traverse_right in eski konumu silinir
		}
		traverse_down = head;
	}
}
