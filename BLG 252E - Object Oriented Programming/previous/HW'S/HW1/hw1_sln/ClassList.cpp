#include "ClassList.h"

ClassList::ClassList(unsigned int new_size){
	max = new_size;
	size = 0;
	list = new Student*[new_size];			
}

ClassList::ClassList(const ClassList &new_list){
	max = new_list.max;
	size = new_list.size; 
	list = new Student*[max];
	for (int i = 0; i < size ; i++)
		list[i] = new_list.list[i];
}

bool ClassList::insert(Student& new_student){
	if (size == max)
		return false;
	else{ 
		list[size] = &new_student;
		size++;
		return true;
	}
}

Student* ClassList::find(int id) const{
	for (int i = 0; i < size; i++)
		if (list[i]->getId() == id)
			return list[i];
	return NULL;
} 

void ClassList::printAll() const{
	for (int i = 0; i < size; i++)
		list[i]->print();
}

ClassList::~ClassList(){
	delete []list;
}
