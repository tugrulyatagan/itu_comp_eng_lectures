// e71.cpp
// Pointers to objects

#include <iostream>				// for IO operations
#include <cString>				// old header file (from C) for String functions
using namespace std;

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
	String *sptr = new String[3];	// Creats 3 objects
	String s1("String_1");			// An objects
	String s2("String_2");			// Another object
	*sptr = s1;							// First elelement of the array
	*(sptr + 1) = s2;					// Second element of the array
	sptr->print();						// Prints the first element
	(sptr+1)->print();				// Prints the second element
	sptr[1].print();					// Prints the second element
	delete[] sptr;						// Objects pointed by sptr are deleted
	return 0;
}