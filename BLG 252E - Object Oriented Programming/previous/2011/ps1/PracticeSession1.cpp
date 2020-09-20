#include <iostream>
using namespace std;

#include "book.h"

// printBook function to print data members of a book object whose reference is given as the input
void printBook(const Book &b){
	cout<<"Book Title= "<<b.getTitle()<<endl;
	cout<<"Author Name= "<<b.getAuthorName()<<endl;
	cout<<"Pages= "<<b.getPages()<<endl;
	cout<<"Year= "<<b.getYear()<<endl;
	cout<<"-----------------------------------------"<<endl;
}

int main(){
	// an array of three book objects
	// created by using the default constructor as no input parameter is given
	Book bookArray[3];
	

	// default values are printed
	printBook(bookArray[0]);

	// book array is set with given values below
	bookArray[0].setAuthorName("H. Deitel and P. Deitel");
	bookArray[0].setTitle("C++ How to Program, Fifth Edition");
	bookArray[0].setYear(2005);
	bookArray[0].setPages(1536);

	bookArray[1].setAuthorName("George B. Thomas, Jr. et al.");
	bookArray[1].setTitle("Thomas' Calculus, 12th Edition");
	bookArray[1].setYear(2009);
	bookArray[1].setPages(1236);

	bookArray[2].setAuthorName("J. K. Rowling");
	bookArray[2].setTitle("Harry Potter and Deathly Hallows");
	bookArray[2].setYear(2007);
	bookArray[2].setPages(784);

	// now the values entered by the user are printed
	for(int i=0;i<3;i++){
		printBook(bookArray[i]);
	}

	// b1 is created by using default constructor as no parameter is given
	Book b1;
	printBook (b1);

    // b2 is created by using the constructor with input parameters
	Book b2("Ari Kovanina Comak Sokan Kiz","S. Larsson",2011,800);
	// so the values entered as input parameters are printed
	printBook (b2);
	
	// b3 is created by using the copy constructor
	Book b3 = bookArray[1];
	printBook (b3);

	return 0;
}

