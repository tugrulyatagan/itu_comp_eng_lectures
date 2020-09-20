#ifndef STACK_H
#define STACK_H
#include "cell.h"

struct Stack{
    StackDataType *head;
    void create();
    void close();
    void push(StackDataType *);
    StackDataType *pop();
    bool isEmpty();
};

#endif
