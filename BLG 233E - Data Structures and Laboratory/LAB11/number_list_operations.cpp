#include <iostream>
#include "number_list.h"

using namespace std;

void Number_list::create(){
	head = NULL;
	tail = NULL;
}

void Number_list::close(){
	Phone_number *p;
	while (head){
		p = head;
		head = head->next;
		delete p;
	}
}

void Number_list::add(Phone_number *nptr){
	Phone_number * newNode = new Phone_number;
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

bool Number_list::isempty(){
	return head == NULL;
}

void Number_list::print(){
	Phone_number *traverse;
	traverse = head;
	while(traverse){
		cout << traverse->phonenum <<endl;
		traverse = traverse->next;
	}
}