// e54.cpp
// Example for Subscript operator [] 

#include <iostream>
#include <string.h>
using namespace std;

class String{
   int size;						// Size of string
	char *contents;				// Pointer to the contents of the string
 public:
	String(const char *);		// constructor
	char & operator[](int);    // subscript operator
	void print() const ;
	~String();						// Destructor
};

// Constructor
String::String(const char *in_data)
{
	 cout<< "Constructor has been invoked" << endl;
	 size = strlen(in_data);
	 contents = new char[size + 1];
	 strcpy(contents, in_data);
}

// Subscript operator
// The operator will be used to access the ith character of the string. 
// If i is less the zero then the first character and 
// if i is greater than the size of the string the last character will be accessed.
char & String::operator[](int i)  
{
   if(i < 0)
      return contents[0];					// return first character
	if(i >= size)
		return contents[size-1];			// return last character
	return contents[i];						// return i th character
}

// This function prints strings on the screen
void String::print() const
{
	 cout<< contents << " " << size << endl;
}

// Destructor
String::~String()
{
	cout<< "Destructor has been invoked" << endl;
	delete[] contents;
}

// ----- Main function -----
int main()
{
	 String s1("String 1");
	 s1[1] = 'p';							// modifies an element of the contents
	 s1.print();
	 cout << " 5 th character of the string s1 is: " << s1[5] << endl;  // prints an element of the contents
	 return 0;
}
