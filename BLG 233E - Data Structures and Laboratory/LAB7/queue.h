#ifndef QUEUE_H
#define QUEUE_H
#include "node.h"

struct Queue{
	Node *head;
	Node *tail;
	void create();
	void close();
	void enqueue(Node *);
	char dequeue();
	bool isempty();
	void print();
};

#endif
