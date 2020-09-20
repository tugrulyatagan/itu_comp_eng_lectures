// This is the part of the source code, where method bodies of Book class are written
#include <cstring> // c library string.h to be able to use strcpy and strlen
#include "book.h"  // user defined headers are included by using ""

// default constructor
Book::Book(){
   int size = strlen("UNNAMED");
   itstitle = new char[size+1];
   itsauthorname = new char[size+1];
   strcpy (itstitle,"UNNAMED");
   strcpy (itsauthorname,"UNNAMED");
   itsyear=0;
   itspages=0;
}

// constructor with input parameters
Book::Book(const char* title,const char* authorname,int year, int pages) {
        int size=strlen(title);
	  	itstitle=new char[size+1];
	    strcpy(itstitle,title);
        size=strlen(authorname);
		itsauthorname=new char[size+1];
		strcpy(itsauthorname,authorname);
	    itsyear = year;
        itspages = pages; 
}

// copy constructor to be able to create a Book object by copying information of another
// Book object whose reference is given as the input parameter
Book::Book(const Book& book_to_copy){
		int size=strlen(book_to_copy.itstitle);
		itstitle=new char[size+1];
	    strcpy(itstitle,book_to_copy.itstitle);
		size=strlen(book_to_copy.itsauthorname);
		itsauthorname=new char[size+1];
		strcpy(itsauthorname,book_to_copy.itsauthorname);
	    itsyear = book_to_copy.itsyear;
		itspages = book_to_copy.itspages;
}

// Destructor - code to run when a book is eliminated
// taken memory for dynamic variables is given back here
Book::~Book() {
	    delete [] itstitle;
		delete [] itsauthorname;
}

// To change itstitle private member of the object with the user given title
void Book::setTitle(const char* title) {
        int size=strlen(title);
	  	itstitle=new char[size+1];
	    strcpy(itstitle,title);


}
// To change itsauthorname private member of the object with the user given authorname
void Book::setAuthorName(const char* authorname) {
        int size=strlen(authorname);
		itsauthorname=new char[size+1];
		strcpy(itsauthorname,authorname);

}
// To change itsyear private member of the object with the user given year
void Book::setYear(int year) {
 itsyear=year;

}
// To change itspages private member of the object with the user given pages
void Book::setPages(int pages) {
	itspages=pages;
}

// To return itstitle private member of the object
char * Book::getTitle() const{
      return itstitle;
}

// To return itsauthorname private member of the object
char * Book::getAuthorName() const{
      return itsauthorname;
}

// To return itspages private member of the object
int Book::getPages() const{
    return itspages ;
}

// To return itsyear private member of the object
int Book::getYear() const{
	return itsyear ;
}
