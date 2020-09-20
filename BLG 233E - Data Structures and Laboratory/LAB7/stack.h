#ifndef STACK_H
#define STACK_H
#include "node.h"

struct Stack{
	Node *head;
	void create();
	void close();
	void push(Node *);
	char pop();
	bool isempty();
	void print();
	bool search(char *);
	int nodecount;
};

#endif
