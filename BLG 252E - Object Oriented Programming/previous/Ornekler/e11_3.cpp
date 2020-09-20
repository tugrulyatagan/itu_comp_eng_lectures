// e11_3.cpp
// http://www.buzluca.info/oop
//		class template "Stack"
#include <iostream>
using namespace std;

template <class Type>
class Stack{
   private:
	  enum {MAX=100};
      Type st[MAX];              // stack: array of any type
      int top;                   // number of top of stack
   public:
	  Stack(){top = 0;}          // constructor
      void push(Type );          // put number on stack
      Type pop();                // take number off stack
};


template<class Type>
void Stack<Type>::push(Type var) // put number on stack
{
   if(top > MAX-1)                // if stack full,
     throw "Stack is full!";      // throw exception
   st[top++] = var;
}

template<class Type>
Type Stack<Type>::pop()          // take number off stack
{
   if(top <= 0)                  // if stack empty,
        throw "Stack is empty!"; // throw exception
   return st[--top];
}

int main()
{
   Stack<float> s1;       // s1 is object of class Stack<float>
   
   try{	
     s1.push(1111.1);       // push 3 floats, pop 3 floats
     s1.push(2222.2);
     s1.push(3333.3);
     cout << "1: " << s1.pop() << endl;
     cout << "2: " << s1.pop() << endl;
     cout << "3: " << s1.pop() << endl;
   }
   catch(const char * msg)                    // exception handler
   {
      cout << msg << endl;
   }

   Stack<long> s2;        // s2 is object of class Stack<long>

   try{	
     s2.push(123123123L);   // push 3 longs, pop 3 longs
     s2.push(234234234L);
     s2.push(345345345L);
     cout << "1: " << s2.pop() << endl;
     cout << "2: " << s2.pop() << endl;
     cout << "3: " << s2.pop() << endl;
   }
   catch(const char * msg)                    // exception handler
   {
      cout << msg << endl;
   }
	return 0;
}

