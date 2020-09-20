// e10_4.cpp
// http://www.buzluca.info/oop
// Throwing exceptions in constructors **/
#include <iostream>
#include <cstring>
using namespace std;

class String{
	enum {MAX_SIZE=10};
	int size;
	char *contents;
 public:
	String(const char *);   // Constructor
	void print()const;      // A member function
	~String();              // Destructor
};

String::String(const char *in_data)
{
	cout<< "Constructor has been invoked" << endl;
	size = strlen(in_data);
	if (size > MAX_SIZE) throw "String too long";
	contents = new char[size +1];   // +1 for null character
	strcpy(contents, in_data);
 }

void String::print() const
{
	 cout<< contents << " " << size << endl;
}

String::~String()
{
	 cout<< "Destructor has been invoked" << endl;
	 delete contents;
}

int main()
{
	char input[20];
	String *str;
	bool again;
	do{
		again = false;
		cout << " Enter a string: ";
		cin >> input;
		try{
			str= new String(input);              // calls the constructor
		}
		catch (const char *a){
			cout << a << endl;
			again = true;
		}
	}while(again);
	str->print();
	delete str;
	return 0;
}
