#include "stack.h"
#include <iostream>
using namespace std;

void Stack::create(){
    head = NULL;
}

void Stack::close(){
    StackDataType *p;
    while (head){
        p = head;
        head = head->next;
        delete p;
    }
}

void Stack::push(StackDataType *newdata){
	StackDataType *newcell = new StackDataType;
	*newcell = *newdata;
	newcell->next = head;
	head = newcell;
}

StackDataType *Stack::pop(){
	StackDataType *topcell = head;
	head = head->next;
	return topcell;
}

bool Stack::isEmpty(){
    return head==NULL;
}
