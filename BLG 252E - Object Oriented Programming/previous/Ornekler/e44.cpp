// e44.cpp
//	An example for the Copy Constructor

#include <iostream>
#include <cstring>			// for string functions
using namespace std;

// A class to define strings
// contents of strings terminate with a null character '\0'
class String{
	 int size;						// Length of the string
	 char *contents;
 public:
	 String(const char *);		// Constructor
	 String(const String &);  	// Copy Constructor
	 void print();					// Prints the string on the screen
	 ~String();						// Destructor
};

// Constructor
// copies the input character array to the contents of the string
String::String(const char *in_data)
{
	 cout<< "Constructor has been invoked" << endl;
	 size = strlen(in_data);
	 contents = new char[size +1];   // +1 for null character
	 strcpy(contents, in_data);		// input_data is copied to the contents
 }

// Copy Constructor
String::String(const String &object_in)   
{
	 cout<< "Copy Constructor has been invoked" << endl;
    size = object_in.size; 
    contents = new char[size + 1];      	//  +1 for null character
    strcpy(contents, object_in.contents); 
} 

void String::print()
{
	 cout<< contents << " " << size << endl;
}

// Destructor
// Memory pointed by contents is given back to the heap
String::~String()
{
	 cout << "Destructor has been invoked" << endl;
	 delete[] contents;
}

//------- Main Function -------
int main()
{

	String my_string("string 1");
	my_string.print();
	String other = my_string;			// Copy constructor is invoked
	String more(my_string);			// Copy constructor is invoked
	other.print();
	more.print();
	return 0;
}
