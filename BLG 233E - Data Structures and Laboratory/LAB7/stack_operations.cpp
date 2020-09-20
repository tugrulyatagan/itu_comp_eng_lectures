#include <iostream>
#include <iomanip>
#include "stack.h"
using namespace std;

void Stack::create(){
	head = NULL;
	nodecount = 0;
}

void Stack::close(){
	Node *p;
	while (head){
		p = head;
		head = head->next;
		delete p;
	}
}

void Stack::push(Node *nptr){
	Node * newNode = new Node;
	*newNode = *nptr;
	newNode->next = head;
	head = newNode;
	nodecount++;
}

char Stack::pop(){
	Node *topNode;
	char temp;
	topNode = head;
	head = head->next;
	temp = *topNode->data;
	delete topNode;
	nodecount--;
	return temp;
}

bool Stack::isempty(){
	return head == NULL;
}

void Stack::print(){
	Node *traverse;
	traverse = head;
	for(int b = 0; b < AREA_CAPATICTY - nodecount; b++)
		cout << "     ";
	while(traverse){
		cout << setw(5) << traverse->data;
		traverse = traverse->next;
	}

}

bool Stack::search(char *plate){
	Node *traverse;
	traverse = head;
	while(traverse){
		if(traverse->data == plate)
			return 1;
		traverse = traverse->next;
	}
	return 0;
}