#include <iostream>
#include <iomanip>
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

void Stack::push(Leaf*ptr){
	Node * newNode = new Node;
	newNode->data = ptr;
	newNode->next = head;
	head = newNode;
}

Leaf *Stack::pop(){
	Node *topNode;
	Leaf* temp;
	topNode = head;
	head = head->next;
	temp = topNode->data;
	delete topNode;
	return temp;
}

bool Stack::isempty(){
	return head == NULL;
}

void Stack::print(){
	Node *traverse;
	traverse = head;
	while(traverse){
		cout << traverse->data->number << setw(3) << " ";
		traverse = traverse->next;
	}
}

bool Stack::search(int num){
	Node *traverse;
	traverse = head;
	while(traverse){
		if(traverse->data->number == num)
			return 1;
		traverse = traverse->next;
	}
	return 0;
}
