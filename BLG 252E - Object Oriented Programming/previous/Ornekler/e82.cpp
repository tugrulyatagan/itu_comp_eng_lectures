// e82.cpp
// virtual functions 
// http://www.buzluca.info/oop/

#include <iostream>
#include <string>
using namespace std;

class Teacher{											// Base class
	string name;
	int numOfStudents;
	public:
	Teacher(const string & new_name,int nos){ // Constructor of base
			name=new_name;numOfStudents=nos;
	}
	virtual void print() const;					// print is a virtual function
};

void Teacher::print() const						// virtual function
{
	cout << "Name: "<< name << endl;
	cout << " Num of Students:"<< numOfStudents << endl;
}

class Principal : public Teacher{				// Derived class
	string SchoolName;
	public:
		Principal(const string & new_name,int nos, const string & sn)
					 :Teacher(new_name,nos)
		{
			SchoolName=sn;
		}
		void print() const;
};

void Principal::print() const						// virtual function
{
	Teacher::print();
	cout << " Name of School:"<< SchoolName << endl;
}

// Show is system which operates on Teachers and Pricipals
void show (const Teacher * tp)
{
	tp->print();       // which print compare with example e81.cpp
}

// A main program to test the show function.
int main()
{
	Teacher t1("Teacher 1",50);
	Principal p1("Principal 1",40,"School");
	Teacher *ptr;
	char c;
	cout << "Teacher or Principal "; cin >> c;
	if (c=='t') ptr=&t1;
	    else    ptr=&p1;
	show(ptr);					// which print compare with example e81.cpp
	return 0;
}
