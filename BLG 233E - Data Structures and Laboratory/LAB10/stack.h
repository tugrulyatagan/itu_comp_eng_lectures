#ifndef STACK_H
#define STACK_H
#include "node.h"
#include "Leaf.h"

struct Stack{
	Node *head;
	void create();
	void close();
	void push(Leaf*);
	Leaf* pop();
	bool isempty();
	void print();
	bool search(int);
};

#endif
