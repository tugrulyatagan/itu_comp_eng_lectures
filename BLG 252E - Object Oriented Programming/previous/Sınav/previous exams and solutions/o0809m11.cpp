// OOP 1st Midterm Exam. 09.03.2009
// Question 1
#include <iostream>
using namespace std;
class A {
    
   public:
      A(){
	   cout <<"A()" << endl ;
      }
      A(const A & ){
	    cout << "A(const A &)" << endl ;
      }
      ~A(){
	    cout << "~A()" << endl ;
      }
};

class B {
      A data;
      A *pointer;
   public:
      B(){
		cout << "B()" << endl ;
      }
      ~B(){
	    cout << "~B()" << endl ;
       }   
      void f1(A objA){
         cout << "f1()" << endl ;
      }   
	  void f2(const A & objA){
         cout << "f2()" << endl ;
      }
	  void f3(){
         pointer = new A;
         cout << "f3()" << endl ;
      }
	  void f4(){
	     A local;
		 delete pointer;
         cout << "f4()" << endl ;
      }  	
};

int main(){
    A objA;
	B objB;
	B *ptrB;
	objB.f1(objA);
	objB.f2(objA);
	objB.f3();
	objB.f4();
	{
	    cout << "Start of the inner block" << endl;
		ptrB = new B;
		A innerA;
	}
	cout << "After the inner block" << endl;
    delete ptrB;
    return 0;
}