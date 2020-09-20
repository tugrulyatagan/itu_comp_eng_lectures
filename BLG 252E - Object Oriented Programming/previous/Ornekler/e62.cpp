// e62.cpp
//	Example of basic inheritance
#include <iostream>
#include <string>
using namespace std;

class Teacher{					// Base class
 protected:						// public for derived class
	string name;
	int age,numOfStudents;
 public:
	void setTeacher (const string &, int , int);
	void print() const;
};

void Teacher::setTeacher (const string &new_name,int a,int nos)
{
	name=new_name;
	age=a;
	numOfStudents=nos;
}

void Teacher::print() const       // Print method of Teacher class
{
	 cout <<"Name: "<< name<<"  Age: "<< age<< endl;
	 cout << "Number of Students: " <<numOfStudents << endl;
}

// ***** Principal is derived from Teacher *****
class Principal : public Teacher{  // Derived class
	string school_name;
	int numOfTeachers;
  public:
	void setPrincipal(const string &, int ,int ,int, const string &);
	void print() const;      // Print function of Principal class
};

void Principal::setPrincipal(const string &new_name,int a,int nos,int no, const string &sch)
{
	setTeacher(new_name,a,nos);
	numOfTeachers=no;
	school_name=sch;
}

void Principal::print() const    // Print method of Principal class
{
	 Teacher::print();				// invokes the print function of the Teacher class
	 cout <<"Name of the school: "<< school_name << endl;
}

// --- Main Function ---
int main()
{
	Teacher t1;
	Principal p1;
	p1.setPrincipal("Principal 1",50,100,20,"School1");
	t1.setTeacher("Teacher 1",35,40);
	p1.print();
	t1.print();
	return 0;
}
