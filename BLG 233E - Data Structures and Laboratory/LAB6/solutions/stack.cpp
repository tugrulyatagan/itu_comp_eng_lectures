#include "stack.h"
#include <iostream>
using namespace std;

void Stack::create(){
    head = NULL;
}

void Stack::makeEmpty(){
    Node *p;
    while (head){
        p = head;
        head = head->next;
        delete p;
    }
}

void Stack::push(char toPush){
    Node *newNode = new Node;
    newNode->data = toPush;
    newNode->next = head;
    head = newNode;
}

char Stack::pop(){
    if (head == NULL)
		return '\0';
    Node *topStack;
    char toReturn;
    topStack = head;
    head = head->next;
    toReturn = topStack->data;
    delete topStack;
    return toReturn;
}

char Stack::getHeadChar(){
    if (head == NULL)
		return '\0';
    return head->data;
}

bool Stack::isEmpty(){
    return head==NULL;
}

void Stack::print(){
    cout<<"Stack contents : ";
    Node *p = head;
    while (p){
        cout<<p->data<<" ";
        p = p->next;
    }
    cout<<endl;
}
