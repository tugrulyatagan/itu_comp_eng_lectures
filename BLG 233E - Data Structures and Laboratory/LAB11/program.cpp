#include <iostream>
#include <stdlib.h>
#include <iomanip>

#include "tree.h"

using namespace std;

typedef Phone_node Phone_Record;
typedef Tree Datastructure;

Datastructure book;

void print_menu();
bool perform_operation(char);
void search_record();
void remove_record();
void update_record();
void print_list();
void add_record();

int main()
{	
	book.create();	
	bool end = false; 
	char choice; 	
	while (!end)
	{ 
		print_menu(); 
		cin >> choice;
		end = perform_operation(choice); 
	} 	
	book.close();
	return EXIT_SUCCESS;
}

void print_menu()
{
//	system("clear"); 
	cout << endl << endl;
	cout << "Phone Book Application" << endl;
	cout << "Choose an operation" << endl;
	cout << "S: Record Search" << endl;
	cout << "A: Record Add" << endl;
	cout << "U: Record Update" << endl;
	cout << "D: Record Delete" << endl;	
	cout << "L: Record List" << endl;
	cout << "E: Exit" << endl;	
	cout << endl;
	cout << "Enter a choice {S, A, U, D, L, E} : ";	
}

bool perform_operation(char choice)
{
	bool terminate = false;
	switch (choice) { 
		case 'S': case 's': 
			search_record();
			break; 
		case 'A': case 'a': 
			add_record();
			break; 
		case 'U': case 'u': 
			book.update();
			break;
		case 'D': case 'd': 
			remove_record();
			break;
		case 'L': case 'l':
			print_list();
		break;
		case 'E': case 'e': 
			cout << "Are you sure you want to exit the program? (Y/N):";
			cin >> choice;
			if ( choice == 'Y' || choice == 'y' )
				terminate = true; 
				break; 
		default: 
			cout << "Error: You have entered an invalid choice" << endl; 
			cout << "Please try again {S, A, U, D, C, E} :" ;
			cin >> choice;
			terminate = perform_operation(choice);
			break; 
	}
	return terminate;
}

void search_record() {
	char name[NAME_LENGTH];
	cout << "Please enter the name of person you want to search for (Press '*' for complete list): " << endl;
	cin.ignore(1000, '\n');
	cin.getline(name, NAME_LENGTH);
	if ( book.search(name) == 0 ) 
		cout << "Could not find record matching search criteria" << endl;
	getchar();
}

void update_record() {

}

void remove_record() {
	char name[NAME_LENGTH];
	char choice;
	cout << "Please enter name of person you want to delete:" << endl;
	cin.ignore(1000, '\n');
	cin.getline(name,NAME_LENGTH);
	int personcount = book.search(name);
	if (personcount == 0)
		cout << "Could not find record matching search criteria" << endl;
	else {
		cout << "Is this the record you want to delete?(y/n)";
		do {
			cin >> choice;
		} while (choice != 'y' && choice != 'n');
		if (choice == 'n') return;
			book.remove(name);
		cout << "Record removed" <<endl;
	}
}



void print_list(){
	char all = '*';
	book.search(&all);
}


void add_record(){
	Phone_node *newnode = new Phone_node;
	newnode->number_head = new Phone_number;
	cout << "Please enter the information for the person you want to record" << endl;
	cout << "Name : " ;
	cin.ignore(1000, '\n');
	cin.getline(newnode->name, NAME_LENGTH);

	newnode->number_head = NULL;
	char num[PHONENUM_LENGTH] = {};

	for(int i=0; i < 20; i++){
		Phone_number *other = new Phone_number;
		cout << i +1 << ". Phone number (0 exit) : ";
		cin >> setw(PHONENUM_LENGTH) >> num;
		if(num[0] == '0')
			break;
		strcpy(other->phonenum,num);

		if(newnode->number_head == NULL){
			newnode->number_head = other;
			newnode->number_head->next = NULL;
			newnode->number_tail = newnode->number_head;
		}
		else{
			newnode->number_tail->next = other;
			newnode->number_tail = newnode->number_tail->next;
			other->next = NULL;
		}
	}
	newnode->left = NULL;
	newnode->right = NULL;

	book.add(newnode);
}