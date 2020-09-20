// e56.cpp
// Overloading of the function call operator
// The function call operator is overloaded to copy a part of the contents of a String
// into a given memory location.
 
#include <iostream>
#include <cString>
using namespace std;

class String{
	int size;
	char *contents;
 public:
	String();                //default constructor
	String(const char *);    // constructor
	void operator()(char *, int) const;  // Function call operator
	~String();               // Destructor
};

// Default Constructor
// Creates an empty string (only NULL character)
String::String()           		   
{
	cout<< "Default constructor has been invoked" << endl;
	size = 0; contents = new char[1];
	strcpy(contents, "");
}

// Constructor
String::String(const char *in_data)
{
	 cout<< "Constructor has been invoked" << endl;
	 size = strlen(in_data);
	 contents = new char[size + 1];			// allocate mem. for the string, +1 is for NULL
	 strcpy(contents, in_data);
 }

// The function call operator: Copies a part of contents into dest.
//		dest is destination memory location,
//		num is number of characters to be copied
void String::operator()(char * dest, int num) const
{
	if (num>size) num=size;				// numbers of characters to be copied may not exceed the size
	for (int k=0; k< num; k++)
		  dest[k]=contents[k];
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
	String s1("Example Program");
	char *c=new char[8];						// Destination memory
	s1(c,7);										// Function call operator is invoked
	c[7]='\0';									// End of String (null)
	cout << c << endl;
	delete[] c;
	return 0;
}