#include "ClassList.h"
#include <iostream>
using namespace std;

ClassList::ClassList(int eleman_sayisi){
	for(int i=0 ; i< eleman_sayisi ; i++){	
		List[i] = new Student(0);			//Allocating memory for List pointer array 
		if(!List[i]){
			cout<<"Failure in allocating memory\n";
			return;
		}
	}
	counter = eleman_sayisi;
	max_stu = counter ;
}

bool ClassList::insert(Student &new_student){	//Parameter is reference since using less memory
	max_stu--;			//This is declining since with this we will notice List is full or not
	if(max_stu >=0 ){	
		*List[max_stu] = new_student;		//Element of List is placing with high indis to low indis (4,3,2,1,0)
		return true;
	}
	return false;	//If List is full, return false
}

void ClassList::printAll() const{
	for(int i=counter-1 ; i>=0; i--){	//We placed Student to List with starting highest indis, so we need to print with highest indis to lowest indis
		List[i]->print();
                cout<<"\n";
        }
}

Student* ClassList::find(int number){
	for(int i=0 ; i<counter ; i++){
		if(List[i]->get_id() == number){	
			return List[i];
		}
	}
	return NULL;	//If id is not found
}

ClassList::ClassList(const ClassList &a){
    counter = a.counter ;	
    max_stu = a.max_stu ;
    for(int i=0; i<counter; i++){
        List[i] = new Student(0);				//First we need to allocate memory for new ClassList
        List[i]->id = a.List[i]->id;			//Id's are equalized
        List[i]->name = a.List[i]->name;		//Name's are equalized
        List[i]->surname = a.List[i]->surname;	//Surname's are equalized
    }
}

ClassList::~ClassList(){
	for(int i=0;i<MAX; i++){		//For all indis i
		delete List[i];				//List is a pointer array of Student class, so we need this line
	cout<<"DESTRUCTOR HAVE BEEN CALLED\n";		//Here is a control line for destructor is working properly or not
	}
}
