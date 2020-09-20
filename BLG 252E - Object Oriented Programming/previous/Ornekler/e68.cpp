// e68.cpp
// COPY CONSTRUCTOR,ASSIGNMENT OPERATOR AND INHERITANCE 
#include <iostream>
#include <cString>
using namespace std;

class String{
 protected:
	int size;
	char *contents;
 public:
	String();         			                  // default constructor
	String(const char *);								// constructor
	String(const String &); 			            // copy constructor
	const String& operator=(const String &);		// assignment operator
	void print() const;									// an ordinary memeber function
	~String();												// destructor
};

String::String()           							// Default Constructor
{
	cout<< "Default constructor of String has been invoked" << endl;
	size = 0; contents = new char[1];
	strcpy(contents, "");

}
// ***** Constructor ******
String::String(const char *in_data)
{
	 cout<< "Constructor of String has been invoked" << endl;
	 size = strlen(in_data);
	 contents = new char[size + 1];
	 strcpy(contents, in_data);
}

String::String(const String &in_object)   // Copy Constructor
{
	cout<< "Copy constructor of String has been invoked" << endl;
	size = in_object.size;
	contents = new char[size + 1];
	strcpy(contents, in_object.contents);
}

const String& String::operator=(const String &in_object) // Assignment operator
{
	cout<< "Assignment operator of String has been invoked" << endl;
	delete[] contents;              // delete old contents
	size = in_object.size;
	contents = new char[size+1];
	strcpy(contents, in_object.contents);
	return *this;
}

void String::print() const
{
	cout<< contents << " " << size << endl;
}

String::~String()
{
	cout << "Destructor of String" << endl;
	delete[] contents;
}

// **** String2 is derived from String
// we will write its own constructors and assignment operaor
//
class String2 : public String{
	int size2;
	char *contents2;
 public:
	String2();         			                     // default constructor
	String2(const char *,const char *);          // constructor
	String2(const String2 &); 			             // copy constructor
	const String2& operator=(const String2 &);   // assignment operator
	void print() const;					                 // An ordinary member function
	~String2();                                  // Destructor
};

String2::String2()           		         // Default Constructor
{
	cout<< "Default constructor of String2 has been invoked" << endl;
	size2 = 0; contents2 = new char[1];
	strcpy(contents2, "");

}

// ** Constructor **
String2::String2(const char *in_data1, const char *in_data2)
				: String(in_data1)                           // initialize String
{
	 cout<< "Constructor of String2 has been invoked" << endl;
	 size2 = strlen(in_data2);
	 contents2 = new char[size2 + 1];
	 strcpy(contents2, in_data2);
}
//** Copy Constructor of String2 **
String2::String2(const String2 &in_object):String(in_object)
{
	cout<< "Copy constructor of String2 has been invoked" << endl;
	size2 = in_object.size2;
	contents2 = new char[size2 + 1];
	strcpy(contents2, in_object.contents2);
}
//** Assignment operator **
const String2& String2::operator=(const String2 &in_object)
{
	String::operator=(in_object);
	cout<< "Assignment operator of String2 has been invoked" << endl;
//	size = in_object.size;
//	contents = new char[strlen(in_object.contents)];
//	strcpy(contents, in_object.contents);
	size2 = in_object.size2;
	delete[] contents2;               // delete old contents
	contents2 = new char[size2 + 1];
	strcpy(contents2, in_object.contents2);
	return *this;
}

void String2::print() const
{
	String::print();
	cout<< contents2 << " " << size2 << endl;
}

String2::~String2()
{
	cout << "Destructor of String2" << endl;
	delete[] contents2;
}

int main()
{
	String2 my_String("String A" , "String B");
	my_String.print();
	String2 other=my_String;    // Copy constructor is invoked
	other.print();
	String2 more;              // Default constructor is invoked
	more=my_String;            // Assignment
	more.print();
	return 0;
}
