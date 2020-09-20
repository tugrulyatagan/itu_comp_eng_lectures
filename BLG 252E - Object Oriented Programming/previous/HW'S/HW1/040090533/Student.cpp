#include "Student.h"
#include <iostream>

Student::Student(){
	cout << "Please enter the id number of the student\n";
	cin>>id;
	cout << "Please enter the name of the student\n";
	cin>>name;
	cout << "Please enter the surname of the student\n";
	cin>>surname;
}

Student::Student(int zero){		//This function is used for only assigning id,number,surname to zero
	if(zero==0){
		id = 0;
		name = "";
		surname = "";
	}
}

void Student::setSurname(const string new_surname){
	surname = new_surname;
}

void Student::print() const{
	cout<< "Student id      : "<< id << endl;
	cout<< "Student name    : "<< name << endl;
	cout<< "Student surname : "<< surname << endl;
}

int Student::get_id() const{
	return id;
}
