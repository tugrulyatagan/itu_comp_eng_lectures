#include <iostream>
#include <iomanip>
#include "queue.h"

using namespace std;

void Queue::create(){
	head = NULL;
	tail = NULL;
}

void Queue::close(){
	Node *p;
	while (head){
		p = head;
		head = head->next;
		delete p;
	}
}

void Queue::enqueue(Node *nptr){
	Node * newNode = new Node;
	*newNode = *nptr;
	if(isempty())
	{
		head = newNode;
		head->next = NULL;
		tail = head;
	}
	else
	{
		tail->next = newNode;
		tail = tail->next;
		tail->next = NULL;
	}
}

char Queue::dequeue(){
	char temp;
	Node *topNode;
	temp = *head->data;
	topNode = head;
	head = head->next;
	delete topNode;
	return temp;
}

bool Queue::isempty(){
	return head == NULL;
}

void Queue::print(){
	Node *traverse;
	traverse = head;
	while(traverse){
		cout << traverse->data << setw(3) << " ";
		traverse = traverse->next;
	}
}