// e83.cpp
// Example of linked list of objects and polymorphism
// http://www.buzluca.info 

#include <iostream>
#include <string>				// Standard header of C++
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

void Principal::print() const						// Non-virtual function
{
	Teacher::print();
	cout << " Name of School:"<< SchoolName << endl;
}

// *** A class to define nodes of the list ***
class ListNode{
	friend class List;
	const Teacher * element;
	ListNode * next;
	ListNode(const Teacher &);	// constructor
};

ListNode::ListNode(const Teacher & n)
{
	element = &n;
	next = 0;
}



// *** class to define a linked list of teachers and principals ***
class List{   // linked list for teachers
	 ListNode *head;
	public:
	 List(){head=0;}
	 bool append(const Teacher &);
	 void print() const ;
	 ~List();
};

// Append a new teacher to the end of the list
// if there is no space returns false, otherwise true
bool List::append(const Teacher & n)
{
	ListNode *previous, *current;
	if(head)        // if the list is not empty
	{
		previous=head;
		current=head->next;
		while(current)             // searh for the end of the list
		{
			previous=current;
			current=current->next;
		}
		previous->next = new ListNode(n);
		if (!(previous->next)) return false;		// If memory is full
	}
	else             // if the list is empty
	{
		head = new ListNode(n);	// Memory for new node
		if (!head) return false;				// If memory is full
	}
	return true;
}


// Prints all elements of the list on the screen
void List::print() const
{
	ListNode *tempPtr;
	if (head)
	{
	   tempPtr=head;
	   while(tempPtr)
		{
			(tempPtr->element)->print();		// POLYMORPHISM
			tempPtr=tempPtr->next;
		}
	}
   else
	  cout << "The list is empty" << endl;
}

// Destructor
// deletes all elements of the list
List::~List()
{
	ListNode *temp;
	while(head)        // if the list is not empty
	{
		 temp=head;
		 head=head->next;
		 delete temp;
	}
}

// ----- Main Function -----
int main()
{
	Teacher t1("Teacher 1",50);
 	Principal p1("Principal 1",40,"School1");
 	Teacher t2("Teacher 2",60);
 	Principal p2("Principal 2",100,"School2");
	List theList;
	theList.print();
	theList.append(t1);
	theList.append(p1);
	theList.append(t2);
	theList.append(p2);
	theList.print();
	return 0;
}
