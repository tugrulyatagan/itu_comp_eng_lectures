// e10_3.cpp
// http://www.buzluca.info/oop
// throwing and cathing an object as an exception

#include <iostream>
#include <string>
using namespace std;
      
class Error{               // Objects to be thrown
  private:
	const string error_code;
  public:
	  Error (const string & code): error_code(code){}
	  void print() const
	  { cout << error_code << endl ; }
};

class Stack
{
 private:
	unsigned int max_size;  // max. available space in the stack
   int *st;						// pointer to array of integers
   int top;						// index of top of stack
 public:
   Stack(unsigned int);              // constructor
   void push(int);
   int pop();
	~Stack(){ delete []st;}
};

Stack::Stack(unsigned int sz)              // constructor
{ 
	max_size = sz;
	st = new int[sz];
	top = 0;
}

void Stack::push(int var)
{
  if(top > max_size-1)  // if stack full,
     throw Error("Stack is full!"); // throw exception
  st[top++] = var;  // put number on stack
}

int Stack::pop()
{
  if(top <= 0)       // if stack empty,
    throw Error("Stack is empty!"); // throw exception
  return st[--top];  // take number off stack
}



int main()
{
   Stack s1(3);			// A stack with max. size=3
   int value;
   short int response;
   do{
      cout << "Push(1) or Pop(2) Enter 0 to exit" << endl;
	  cin >> response;
	  try{
		 if (response ==1)
		 {
			cout << "Enter a value to push: ";
			cin >> value;
			s1.push(value);
		 }
		 else if(response ==2)
			cout << "From stack: " << s1.pop() << endl;
	  }
      catch(const Error &e)                    // exception handler
      {
        e.print();
      }
   }while(response);
   cout << "Arrive here after catch (or normal exit)" << endl;
	return 0;
}
