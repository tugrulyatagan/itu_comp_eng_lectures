#include <iostream>
#include "stack.h"

using namespace std;

void Stack::create(){
	head = NULL;
}

void Stack::close(){
	Node *p;
	while (head){
		p = head;
		head = head->next;
		delete p;
	}
}

void Stack::push(char newdata){
	Node *newnode = new Node;
	newnode->data = newdata;
	newnode->next = head;
	head = newnode;
}

char Stack::pop(){
	Node *topnode;
	char temp;
	topnode = head;
	head = head->next;
	temp = topnode->data;
	delete topnode;
	return temp;
}

bool Stack::isempty(){
	return head == NULL;
}
