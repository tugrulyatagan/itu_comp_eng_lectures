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

#include <string>		//For string type
#ifndef STUDENT_H
#define STUDENT_H

using namespace std;	

class Student{
	private:
		int id;					//Student id(school number or etc...)
		string name;			//Student's name
		string surname;			//Student's surname
        friend class ClassList;	//This is needed for copy constructor of ClassList class, if ClassList is not friend of Student, then we cannot use copyconstructor
	public:
		Student();						//This function is default constructor of the Student class
		Student(int );					//This function is constructor of Student class with one integer parameter
		int get_id() const;				//This function returns Student's id and it is const function since it does not change anything about Student class
		void print() const;				//This function prints Student id,nane and surname and it is also const function
		void setSurname(const string);	//This function is required for altering Student surname
};

#endif