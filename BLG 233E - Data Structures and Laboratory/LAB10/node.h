#ifndef NODE_H
#define NODE_H
#include "Leaf.h"

struct Node{
	Leaf *data;
	Node *next;
};

#endif
