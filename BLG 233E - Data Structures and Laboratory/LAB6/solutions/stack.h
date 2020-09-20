#ifndef STACK_H
#define STACK_H

struct Node{
    char data;
    Node *next;
};

struct Stack{
    Node *head;
    void create();
    void makeEmpty();
    void push(char);
    char pop();
    // to read the top element without popping
    char getHeadChar();
    bool isEmpty();
    // to print the elements in the stack
    void print();
};

#endif
