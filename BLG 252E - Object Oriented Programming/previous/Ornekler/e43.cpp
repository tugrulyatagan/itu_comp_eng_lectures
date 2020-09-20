// e43.cpp
//	An example for Destructors 

#include <iostream>
#include <cstring>			// for string functions
using namespace std;

// A class to define strings
// contents of strings terminate with a null character '\0'
class String{
	 int size;					// length of a string
	 char *contents;
 public:
	 String(const char *);   // Constructor
	 void print();           // A member function
	 ~String();              // Destructor
};

// Constructor
// copies the input character array that terminates with null character
// to the contents of the string
String::String(const char *in_data)
{
	 cout<< "Constructor has been invoked" << endl;
	 size = strlen(in_data);
	 contents = new char[size +1];   // +1 for null character
	 strcpy(contents, in_data);		// input_data is copied to the contents
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
	 cout << "--------- Start of Blok 1 ------" << endl;
	 String string1("string 1");
	 String string2("string 2");
	 {
		 cout << "--------- Start of Blok 2 ------" << endl;
		 string1.print();
		 string2.print();
		 
		
		 cout << "--------- End of Blok 2 ------" << endl;
	 }
	 cout << "--------- End of Blok 1 ------" << endl;
	 return 0;
 }
