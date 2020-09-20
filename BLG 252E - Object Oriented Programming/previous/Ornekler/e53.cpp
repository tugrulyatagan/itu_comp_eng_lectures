// e53.cpp
// COPY CONSTRUCTOR AND ASSIGNMENT OPERATOR
// Assignment operator in this example can be chained as a=b=c

#include <iostream>				// for IO operations
#include <string.h>				// old header file (from C) for String functions
using namespace std;

// A class to define strings
// contents of strings terminate with a null character '\0'
class String{
	int size;
	char *contents;
 public:
	String();						//default constructor
	String(const char *);		// constructor
	String(const String &);   // copy constructor
	const String& operator=(const String &);  // assignment operator
	void print() const ;
	~String();               // Destructor
};

// Default Constructor
// Creates an empty string (only NULL character)
String::String()           		   
{
	cout<< "Default constructor has been invoked" << endl;
	size = 0;
	contents = new char[1];
	strcpy(contents, "");
}

// Constructor
String::String(const char *in_data)
{
	 cout<< "Constructor has been invoked" << endl;
	 size = strlen(in_data);								// Size of input data
	 contents = new char[size + 1];						// allocate mem. for the string, +1 is for NULL
	 strcpy(contents, in_data);
 }

// Copy Constructor
String::String(const String &in_object)
{
	cout<< "Copy constructor has been invoked" << endl;
	size = in_object.size;
	contents = new char[size+1];
	strcpy(contents, in_object.contents);
}

// Assignment operator
const String& String::operator=(const String &in_object)   
{
	cout<< "Assignment operator has been invoked" << endl;
	size = in_object.size;
	delete[] contents;										// delete old contents
	contents = new char[size+1];
	strcpy(contents, in_object.contents);
	return *this;												// returns a reference to the object	
}

// This method prints strings on the screen
void String::print() const
{
	cout<< contents << " " << size << endl;
}

//Destructor
String::~String()
{
	 cout<< "Destructor has been invoked" << endl;
	 delete[] contents;
}

// ----- Main function -----
int main()
{
	String s1("String 1");
	String s2 = s1;					// Copy constructor is invoked
	s2.print();
	String s3, s4;						// Default constructor is invoked
	s3 = s4 = s2;						// Assignment
	s3.print();
	s4.print();
	return 0;
}
