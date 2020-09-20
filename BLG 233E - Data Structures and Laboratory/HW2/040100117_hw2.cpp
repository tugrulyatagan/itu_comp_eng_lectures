/********************************************
* BLG 233E DATA STRUCTURES AND LABORATORY	*
* CRN: 11146								*
* HOMEWORK 2								*
* STUDENT RECORDS							*
* TUGRUL YATAGAN							*
* 040100117									*
* Input file is "records2.txt"				*
********************************************/
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#define INPUT_FILE "records2.txt" // okunacak dosya
#define OUTPUT_FILE "orderedrecords2.txt" // yazilacak dosya

//node.h
//*********************************************************
struct Node{
	int Number; // integer tipinde numara bilgisi
	float GPA; // float tipinde not bilgisi
	string Name; // isim bilgisi string
	string Department; // bolum bilgisi string
	Node *next; // bir sonraki dugumu gosterir
};


//stack.h
//*********************************************************
struct Stack{
	Node *head;
	void create(); // yigin olusturur
	void close(); // yigini siler
	void push(Node *); // yigina ekler 
	Node *pop(); // yigindan cikarir
	void print(); // yigini ekrana basar
	bool isempty();
};


//stack_operations.cpp
//*********************************************************
void Stack::create(){
	head = NULL;
}

void Stack::close(){
	Node *p;
	while (head){
		p = head;
		head = head->next; // dugumler bastan sirayla silinir
		delete p; // dugumler silinir
	}
}

void Stack::push(Node *newdata){ // Node tipinde isaretci alir
	Node *newnode = new Node;
	*newnode = *newdata;
	newnode->next = head; // yeni dugumu basa ekler
	head = newnode;
}

Node *Stack::pop(){ // Node tipinde isaretci doner
	Node *topnode; //gecici head
	Node *temp = new Node; // gecici dugum
	topnode = head;
	head = head->next; // basi yana kaydirir
	*temp = *topnode; // eski head gecici dugum olur
	delete topnode; // eski head silinir
	return temp;
}

void  Stack::print(){
	Node *traverse = head;
	while(traverse){
		cout << traverse->Number << "\t";
		cout << traverse->Name << "\t";
		cout << traverse->GPA << "\t";
		cout << traverse->Department << endl;
		traverse = traverse->next;
	}
}

bool Stack::isempty(){
	return head == NULL;
}


//program.cpp
//*********************************************************
void readfile(); // dosyayi okur yigina ekler
void writefile(); // yigini dosyaya yazar

Stack S1, S2; // yiginlar global tanimlanir

int main(){
	cout << "STUDENT RECORDS PROGRAM" << endl;
	cout << "BLG 233E DATA STRUCTURES AND LABORATORY" << endl;
	cout << "CRN: 11146" << endl;
	cout << "HOMEWORK 2" << endl;
	cout << "TUGRUL YATAGAN" << endl;
	cout << "040100117" << endl << endl;

	S1.create(); // S1 yigini olusturulur
	S2.create(); // S2 yigini olusturulur

	readfile(); // girdi dosyasi okunur
	cout << "Stack 1 is: " << endl << "------------------" << endl;
	S1.print(); // yigin ekrana basilir

	writefile(); // yigin dosyaya yazilir
	S1.close(); // S1 yigini silinir
	S2.close(); // S2 yigini silinir
	return 0;
}

void readfile(){
	ifstream input; // girdi dosyasi "input"
	input.open(INPUT_FILE, ios::in); // okumak icin dosya acilir
	if(input.is_open()){ // dosya basariyla acilirsa
		while(input.good()){ // dosya oldugu surece
			Node *newnode = new Node; // dinamik dugum alinir

			// burada dosya okunur
			input >> newnode->Number; // numara okunur
			if (newnode->Number < 0) // dosya sonundaki satir sonu karakteri kontrolu
				break; // dosyanin sonuna gelmisse durur
			input >> newnode->Name; // isim okunur
			input >> newnode->GPA; // not okunur
			input >> newnode->Department; // bolum okunur
			
			// burada dugum yigina eklenir
			newnode->next = NULL;
			if(S1.isempty()) // S1 bos ise
				S1.head = newnode; // yeni dugumu basa ekle
			else if (newnode->GPA > S1.head->GPA){ // yeni dugum en buyukten buyukse
				newnode->next = S1.head; // yeni dugumu basa ekle
				S1.head = newnode;
			}
			else if(newnode->GPA < S1.head->GPA){ // yeni dugum en buyukten kucukse
				while(!S1.isempty() && newnode->GPA <= S1.head->GPA) // yeni dugum en kucuk olmadigi ve en buyukten kucuk oldugu surece(ayni not degerinde olsa da)
					S2.push(S1.pop()); // S1 den al S2 ye aktar
				while(newnode->GPA == S2.head->GPA && (newnode->Name.compare(S2.head->Name) < 0)) // eger yeni dugum ile S2 basindaki dugum esit ve
					S1.push(S2.pop()); // yeni dugumun alfabetik sirasi S2 nin basindakinden kucuk oldugu surece S2 den al S1 e aktar
				newnode->next = S1.head; // yeni dugumu basa ekle
				S1.head = newnode;
				while(!S2.isempty()) // S2 bitene kadar
					S1.push(S2.pop()); // herseyi S1 e aktar
			} // else if kapanir
		} // while kapanir
		input.close(); // dosya kapatilir
	} // if kapanir
	else{
		cerr << "Input file can not be opened!" << endl; // dosya acilamazsa
		exit(1);
	}
}

void writefile(){
	ofstream output; // cikti dosyasi "output"
	output.open(OUTPUT_FILE, ios::out); // yazmak icin dosya acilir
	Node *traverse = S1.head; // traverse basa esiitlenir
	if(output.is_open()){ // dosya basariyla acilirsa
		while(traverse){ // dugum oldugu surece
			output << traverse->Number << "\t";
			output << traverse->Name << "\t";
			output << traverse->GPA << "\t";
			output << traverse->Department << "\t";
			output << endl;
			traverse = traverse->next; //bir sonraki dugum
		}
		output.close(); // dosya kapatilir
		cout << "The file is succesfuly writen." << endl;
	}
	else // dosya yazilamazsa
		cout << "Unable to write file!";
}
