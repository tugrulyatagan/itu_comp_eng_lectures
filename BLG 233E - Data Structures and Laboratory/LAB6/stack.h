#include "node.h"

struct Stack{
	Node *head;
	void create();
	void close();
	void push(char);
	char pop();
	bool isempty();
};
