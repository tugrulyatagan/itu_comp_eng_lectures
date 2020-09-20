// list.cpp 
// Defining the operations that we can perform on the list

#include <iostream> // allows program to perform input and output
//#include <stdlib.h> // contains function prototypes for memory allocation
#include <string.h> // program uses C++ standard string class 
#include "list.h" // include definition of struct List

using namespace std;  // enables the program to use all the names in any included standard C++ header 

// create list
void List::create()
{
	head = NULL; // create empty list  
	nodecount = 0; // initialize nodecount to 0
}

void List::print(){
	Phone_node *p = head;
	int i = 1;
	while(p)
	{
		cout << i++ << ".   " << p->name << "   " << p->phonenum << endl;
		p = p->next;
	}
}
// close list 
void List::close()
{
	makeEmpty();
}

// empty out the list 
void List::makeEmpty()
{
	Phone_node *p;
	while (head){
		p = head;
		head = head->next;
		delete[] p->name;
		delete[] p->phonenum;
		delete p;
	}
	nodecount = 0;
}

// insert new phone record into list 
void List::insert(Phone_node *newnode)
{
	Phone_node *traverse, *tail;
	traverse = head;
	newnode->next = NULL;

	if (head == NULL){ // first node being added
		head = newnode;
		nodecount++;
		return;
	}

	if ( strcmp(newnode->name, head->name) < 0 ){ // insert to head of list (newnode's name comes before head's)
		newnode->next = head;
		head = newnode;
		nodecount++;
		return;
	}

	while ( traverse && ( strcmp(newnode->name, traverse->name) > 0) ){ // (newnode's name comes after head's)
		tail = traverse;
		traverse = traverse->next;
	}

	if (traverse){ // insert into a position
		newnode->next = traverse;
		tail->next = newnode;
	}
	else // insert to end
		tail->next = newnode;
	nodecount++;
}

// remove phone record from list
void List::remove(int ordernum)
{   
	Phone_node *traverse, *tail;
	int counter = 1;
	traverse = head;

	if ( ordernum <= 0) { 
		cout << "Invalid record order number.\n";
		return;
	}

	if ( ordernum == 1 ) {
		head = head ->next;
		delete traverse;
		nodecount--;
		return;
	}

	while ( (traverse != NULL) && (counter < ordernum) ) {
		tail = traverse;
		traverse = traverse->next;
		counter++;
	}

	if (counter < ordernum){ // given order num too large
		cout << "Could not find record to delete.\n";
	}
	else { // record found
		tail->next=traverse->next;
		delete[] traverse->name;
		delete[] traverse->phonenum;
		delete traverse;
		nodecount--;
	}
}
	
		
// search the list for a name 
Phone_node* List::search(char *target)
{
	Phone_node *traverse;
	List result;
	result.create();
	int counter = 0;
	int found = 0;
	traverse = head;
	bool all = false;

	if ( strcmp(target,"*") == 0 ) // compare the string target to the string "*", if they are equal do the following
		all = true;

	while (traverse) {
		counter++;
		if (all) {
			cout << counter << "." << traverse->name << " " << traverse->phonenum << endl;
			found++;
		}
		else if ( strnicmp(traverse->name, target, strlen(target)) == 0 && strcmp(traverse->name, target) <= 0){ // if strings traverse->name and target are equal up to the length of target (case-insensitive) 
			found++;
			cout << counter << "." << traverse->name << " " << traverse->phonenum << endl;		
			result.insert(traverse);
		}		
		traverse = traverse->next;		
	}
	return result.head;
}

// update a phone record in the list 
void List::update(int recordnum, Phone_node *newnode)
{
	remove(recordnum);
	insert(newnode);
}
