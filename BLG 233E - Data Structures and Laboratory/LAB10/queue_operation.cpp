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

void Queue::enqueue(Leaf *ptr){
	Node * newNode = new Node;
	newNode->data = ptr;
	if(isempty()){
		head = newNode;
		head->next = NULL;
		tail = head;
	}
	else{
		tail->next = newNode;
		tail = tail->next;
		tail->next = NULL;
	}
}

Leaf *Queue::dequeue(){
	Leaf* temp;
	Node *topNode;
	temp = head->data;
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
		cout << traverse->data->number << setw(3) << " ";
		traverse = traverse->next;
	}
}

bool Queue::search(int num){
	Node *traverse;
	traverse = head;
	while(traverse){
		if(traverse->data->number == num)
			return 1;
		traverse = traverse->next;
	}
	return 0;
}
