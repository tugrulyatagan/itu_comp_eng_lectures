#ifndef STUDENT_H_
#define STUDENT_H_

#include <iostream>
using namespace std;

class Student{
	int id;						
	char name[20];
	char surname[30];
public:
	Student();					//Default Constructor
	Student(int, const char*, const char*);	//Constructor with arguments, not used in the test program of the assignment
	void setId(int new_id){		
		id=new_id;
	}	
	void setName(const char* new_name){
		strcpy(name, new_name);
	}
	void setSurname(const char* new_surname){
		strcpy(surname, new_surname);
	}
	int getId() const{
		return id;
	}
	void print() const;
};

#endif //STUDENT_H_
