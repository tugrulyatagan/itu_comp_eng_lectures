// This is the header file where only the class declaration is done with defining attributes
// and giving method prototypes.

// to include the header once
#ifndef BOOK_H
#define BOOK_H

class Book {
	// private members
		char *itstitle;
		char *itsauthorname;
		int itsyear;
		int itspages;	
    // public members(methods to be used outside of the class)
	public: 
		Book();
        Book(const char* title,const char* authorname, int year, int pages);
		Book(const Book& book_to_copy);
        ~Book();
        void setTitle(const char* title);
		void setAuthorName(const char* authorname);
		void setYear(int year);
		void setPages(int pages);
		char* getTitle() const;
		char* getAuthorName() const;
        int getPages() const;
        int getYear() const;		
};

#endif
