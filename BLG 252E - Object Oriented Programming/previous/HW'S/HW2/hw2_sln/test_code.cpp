//___________________________________________________________________________________________________________
// DO NOT MODIFY THIS TEST CODE AS IT WILL BE USED AS IT IS WHILE GRADING YOUR HOMEWORK!
//___________________________________________________________________________________________________________

#include "person.h"
#include <iostream>
#include <string>  // to be able to use C++ string
#include <list>    // to be able to use STL list
using namespace std;

// a list of strings and an iterator to be able to move on the list
typedef list<string> List;
typedef List::const_iterator Iter; // const_iterator is used to move on const List

// method to check if the given pair can sail across without violating the rules or not
void sailAcross(const Person &p1, const Person &p2, const List &remainders){
	 cout<<p1.getName()<<" and "<<p2.getName()<<" are trying sail across together"<<endl;
	 cout<<"leaving ";
     for(Iter i = remainders.begin(); i != remainders.end(); i++)
         cout<<*i<<" ";
	 cout<<"behind."<<endl;
	 // check if p1 or p2 can operate the raft
	 if ( !p1.canOperateTheRaft() && !p2.canOperateTheRaft() )
	 	 cout<<"ERROR: None of "
		     <<p1.getName()<<" and "<<p2.getName()
			 <<" can operate the raft";
	 // check if p1 and p2 can sail across together, leaving remainders behind 
	 // without violating the rules 
	 else if ( !p1.canGetOnTheRaftWith(p2, remainders) )
	     cout<<"ERROR: Violation of game rules"<<endl; 
	 else 
	     cout<<p1.getName()<<" and "<<p2.getName()
		     <<" can succesfully sail across the river together";
     cout<<endl<<endl;
}

int main(int argc, char *argv[]){
    // a list to contain all 8 people's names and another list for remainders
    List people, remaining_people;
    // creating each person and adding it to the list
    Mother m("Mother");
	people.push_back(m.getName());
    Father f("Father");
	people.push_back(f.getName());
    Daughter d1("Daughter 1"), d2("Daughter 2");
	people.push_back(d1.getName());
	people.push_back(d2.getName());
    Son s1("Son 1"), s2("Son 2");
	people.push_back(s1.getName());
	people.push_back(s2.getName());
    Policeman p("Policeman");
    people.push_back(p.getName());
    Thief t("Thief");
	people.push_back(t.getName());
    
    // Trying sailAcross function for some different combinations
    remaining_people = people;
	remaining_people.remove("Mother");
    remaining_people.remove("Daughter 2");
    sailAcross(m,d2,remaining_people);  
    // ERROR: Father is left with daughter1 without mother's presence.
  
    remaining_people = people;
    remaining_people.remove("Father");
    remaining_people.remove("Daughter 2");
    sailAcross(f,d2,remaining_people);  
    // ERROR: Father is left with daughter2 without mother's presence.
    
    remaining_people = people;
    remaining_people.remove("Son 1");
    remaining_people.remove("Son 2");
    sailAcross(s1,s2,remaining_people);
    // ERROR: None of them can operate the boat.
    
    remaining_people = people;
    remaining_people.remove("Policeman");
    remaining_people.remove("Daughter 1");
    sailAcross(p,d1,remaining_people);
    // ERROR: Thief is left with family without policeman's presence
    
    remaining_people = people;
    remaining_people.remove("Mother");
    remaining_people.remove("Father");
    sailAcross(m,f,remaining_people);
    // OK: This does not violate any rule
    
    return EXIT_SUCCESS;
}
