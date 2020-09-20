#ifndef QUEUE_H
#define QUEUE_H
#include "node.h"
#include "Leaf.h"

struct Queue{
	Node *head;
	Node *tail;
	void create();
	void close();
	void enqueue(Leaf*);
	Leaf* dequeue();
	bool isempty();
	void print();
	bool search(int);
};

#endif
