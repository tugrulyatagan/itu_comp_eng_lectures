// e69.cpp
// Inheritance & composition 
#include <iostream>
using namespace std;

class A {
	int i;
public:
	A(int ii) : i(ii) {cout << endl << "Constructor A";}
	~A() {cout << endl << "Destructor A";}
	void f() const {}
};

class B {
	int i;
public:
	B(int ii) : i(ii) {cout << endl << "Constructor B";}
	~B() {cout << endl << "Destructor B";}
	void f() const {}
};

class C : public B {									// Inheritance,  C is a kind of B  
	A a;													// Composition,  C has A 
public:	
	C(int ii) : B(ii), a(ii) {cout << endl << "Constructor C";}
	~C() {cout << endl << "Destructor C";}    // Calls ~A() and ~B()
	void f() const {									// Redefinition
		a.f();
		B::f();
	}
};

int main() {
	C c(47);
	return 0;
}
