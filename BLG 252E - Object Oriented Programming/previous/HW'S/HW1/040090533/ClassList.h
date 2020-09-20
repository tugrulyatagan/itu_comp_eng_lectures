/*
*
* BLG252E
* 2011 Spring
* 1st Homework
*
*/
/*
*
* Student Name: Abdullah Aydeger
* Student ID : 040090533
*
*/

#ifndef CLASSLIST_H
#define CLASSLIST_H

#include "Student.h"
#define MAX 5		//This is used as 5 since MAX_NUM=5 in TestClassList

class ClassList{
	private:
	    Student* List[MAX];			//This is a pointer array of Student class
	    int counter;				//This is used for holding element number
	    int max_stu;				//This is used for controlling List is full or not
	public:
		ClassList(int);					//This function is constructor of ClassList class with integer parameter
        ClassList(const ClassList&);	//This function is copy constructor of ClassList
		~ClassList();					//This function is destructor of ClassList -needing this since ClassList has pointer private member
		bool insert(Student &a);		//This function used for inserting Student class to List array, and return false or true
		void printAll() const;			//This function prints all the students in the List array
		Student* find(int );			//This function finds the student with its integer parameter
};

#endif

/*********************************** COPY CONSTRUCTOR ******************************************
	We need Copy constructor because if we do not use this then all of the members especially
		pointers (here is its name List) will show same thing. If we want to add one 
			student to one ClassList then the student will be added to other
				ClassList too. For avoiding this we must use copy 
										constructor.

	However, by using copyconstructor in this code, if we want to change one student surname
		(finding student with his/her id) we need to change for all ClassLists. Despite
			of the student is same, we MUST change the student name or surname or
									id for all ClassLists.

		In conclusion, we can use or don't use copy constructor. But I decided to use it...
**********************************************************************************************/