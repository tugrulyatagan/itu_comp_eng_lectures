// list.h
// List struct definition
// Member functions are defined in list.cpp

// prevent multiple inclusions of header
#ifndef LIST_H
#define LIST_H

#include "node.h" // include definition of struct Phone_node

// List struct definition
struct List
{
	Phone_node *head;
	int nodecount;
	char *filename;
	FILE *phonebook;
	void create(); // create list
	void close();
	void makeEmpty();
	void insert(Phone_node *);
	void remove(int ordernum);
	Phone_node* search(char *);   
	void update(int recordnum, Phone_node *);
	void print();
};

#endif
