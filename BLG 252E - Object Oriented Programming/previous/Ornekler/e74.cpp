// e74.cpp
// Example of an Heterogeneous linked list 
#include <iostream>
#include <string>
using namespace std;

class Teacher{
	friend class HetList;
	string name;
	int age,numOfStudents;
	Teacher * next;       // Pointer to next object of Teacher
 public:
	Teacher(const string &, int, int); // Constructor
	void print() const;
};
Teacher::Teacher(const string &new_name,int a,int nos)
{
	name = new_name;
	age=a;
	numOfStudents=nos;
}
void Teacher::print() const        // Print method of Teacher class
{
	 cout <<"Name: "<< name<<"  Age: "<< age<< endl;
	 cout << "Number of Students: " <<numOfStudents << endl;
}

// Principal class is derived from Teacher class
class Principal: public Teacher{
	 string SchoolName;
	public:
	 Principal(const string &, int, int, const string &); // Constructor
	 void print() const ;
};
// Constructor of principal 
Principal::Principal(const string &new_name,int a,int nos, const string &s_name)
									 :Teacher(new_name,a,nos)
{
	SchoolName = s_name;
}

void Principal::print() const         // Print method of principal class
{
	Teacher::print();
	cout <<"Name od School: "<< SchoolName << endl;
}

// ***** Class of het. linked list *****
// It can contain objects of teacher and principal
class HetList{   // Heterogeneous linked list
	Teacher *head;
 public:
   HetList(){head=0;}
	void insert(Teacher *);
	void print();
};

// inserts a new teacher or principla at the beginning of the list
void HetList::insert(Teacher* t)
{
	if(head)        // if the list is not empty
		t->next=head;
	else     			 // if the list is empty
		t->next=0;   // insert 1st element
	head=t;
}

// print the elements of the list
void HetList::print()
{
	Teacher *tempPtr;
	if (head)
	{
		tempPtr=head;
		while(tempPtr)
		{
			tempPtr->print();
			tempPtr=tempPtr->next;
		}
	}
	else
		cout << "The list is empty" << endl;
}

// ----- Main Function -----
int main()
{
	HetList theHetList;
	Teacher *t1=new Teacher("Teacher1",30,50);
	Principal *p1=new Principal("Principla1",60,40,"School1");
	Teacher *t2=new Teacher("Teacher2",40,65);
	theHetList.insert(t1);
	theHetList.insert(p1);
	theHetList.insert(t2);
	theHetList.print();
	return 0;
}
