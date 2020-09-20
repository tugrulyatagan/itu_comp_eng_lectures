#ifndef CLASSLIST_H_
#define CLASSLIST_H_

#include "Student.h"

class ClassList{
	Student** list;  // a dynamically allocated array of pointers to Student objects
	unsigned int size, max;
public:	
	ClassList(unsigned int);	//Constructor
	ClassList(const ClassList&);	//Copy constructor	
	bool insert(Student&);			//Public method, adds a student to the ClassList
	Student* find(int) const;	    //Public method, finds and returns the student pointer 
	void printAll() const;			//Public method, prints the student list
	~ClassList();					//Destructor
};

#endif //CLASSLIST_H_
