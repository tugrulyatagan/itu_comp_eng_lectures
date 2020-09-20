#include "Student.h"

Student::Student() {
	cout << "Enter a new student information.." << endl;
	cout << "id: "; cin >> id;
	cout << "name: "; cin >> name;
	cout << "surname: "; cin >> surname;
}

Student::Student(int new_id, const char *new_name, const char *new_surname) {
	id = new_id;
	strcpy(name, new_name);
	strcpy(surname, new_surname);
}

void Student::print() const{
	cout << id << " " 
		 << name << " " 
		 << surname << endl;
}
