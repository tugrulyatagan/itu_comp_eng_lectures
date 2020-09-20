#include "person.h"
#include <iostream>
using namespace std;

// BODIES OF FUNCTIONS:
//__________________________________________________________________________________________

// a function to look for a name and return true if it is in the list
// and return false if it is not
bool is_in_list(const List& listOfPeople, string name_to_search){
	for(Iter i = listOfPeople.begin(); i != listOfPeople.end(); i++)
		if(*i==name_to_search)
			return true;
	return false;
}

// Father-Daughter Inconsistency: If father and any of the daughters are left behind 
// without mother's presence, it returns true as this is inconsistent with the rules.
// Else it returns false.
bool father_daughter_inconsistency(const List& remainders){
	if(!is_in_list(remainders, "Mother") && is_in_list(remainders, "Father"))
		if(is_in_list(remainders, "Daughter 1") || is_in_list(remainders, "Daughter 2"))
			return true;
	return false;
}

// Mother-Son Inconsistency: If mother and any of the sons are left behind without 
// father's presence, it returns true as this is inconsistent with the rules.
// Else it returns false.
bool mother_son_inconsistency(const List& remainders){
	if(!is_in_list(remainders, "Father") && is_in_list(remainders, "Mother"))
		if(is_in_list(remainders, "Son 1") || is_in_list(remainders, "Son 2"))
			return true;
	return false;
}

// Thief-Family Inconsistency: If thief and any of the family members are left behind 
// without policeman's presence, it returns true as this is inconsistent with the rules.
// Else it returns false.
bool thief_family_inconsistency(const List& remainders){
	if( !is_in_list(remainders, "Policeman") && is_in_list(remainders, "Thief"))
		if(remainders.size()>1)
		   return true;
	return false;
}


// BODIES OF canGetOnTheRaftWith METHOD FOR BASE AND DERIVED CLASSES
//__________________________________________________________________________________________

// canGetOnTheRaftWith method of base class Person
bool Person::canGetOnTheRaftWith(const Person& p2, const List& remainders) const{
	// Thief inconsistency rule applies for all persons, so checking it in the base class
	if ( (name!="Policeman" && p2.name=="Thief") || thief_family_inconsistency(remainders) ){
		 cout<<"Thief is left with a family member without policeman's presence."<<endl;
		 return false;
	}
	return true;
}

// Polymorphic canGetOnTheRaftWith method for Mother class
bool Mother::canGetOnTheRaftWith(const Person& p2, const List& remainders) const{
	// The mother cannot get on the raft with any of her sons.
	if (p2.getName().substr(0,3)=="Son"){
		cout<<"Mother is left with son without father's presence."<<endl;
		return false;
	}
	// The father cannot stay with any of the daughters, without their mother's presence.
    if (father_daughter_inconsistency(remainders)){
		cout<<"Father is left with daughter without mother's presence."<<endl;
		return false;
	}
	// The thief cannot stay with any family member, if the policeman is not there.
	return Person::canGetOnTheRaftWith(p2, remainders);
}

// Polymorphic canGetOnTheRaftWith method for Father class
bool Father::canGetOnTheRaftWith(const Person& p2, const List& remainders) const{
	// The mother cannot get on the raft with any of her sons.
	if (p2.getName().substr(0,3)=="Dau"){
		cout<<"Father is left with daughter without mother's presence."<<endl;
		return false;
	}
	// The mother cannot stay with any of the sons, without their father's presence.
    if (mother_son_inconsistency(remainders)){
		cout<<"Mother is left with son without father's presence."<<endl;
		return false;
	}
	// The thief cannot stay with any family member, if the policeman is not there.
	return Person::canGetOnTheRaftWith(p2, remainders);
}

// Polymorphic canGetOnTheRaftWith method for Daughter class
bool Daughter::canGetOnTheRaftWith(const Person& p2, const List& remainders) const{
	// The father cannot get on the raft with any of her daughters.
	if (p2.getName() == "Father"){
		cout<<"Father is left with daughter without mother's presence."<<endl;
		return false;
	}
	// The father cannot stay with any of the daughters, without their mother's presence.
	if (p2.getName() == "Mother" && father_daughter_inconsistency(remainders)){
		cout<<"Father is left with daughter without mother's presence."<<endl;
		return false;
	}
	// The thief cannot stay with any family member, if the policeman is not there.
	return Person::canGetOnTheRaftWith(p2, remainders);
}

// Polymorphic canGetOnTheRaftWith method for Son class
bool Son::canGetOnTheRaftWith(const Person& p2, const List& remainders) const{
	// The mother cannot get on the raft with any of her sons.
	if (p2.getName() == "Mother"){
		cout<<"Mother is left with son without father's presence."<<endl;
		return false;
	}
	// The mother cannot stay with any of the sons, without their father's presence.
	if (p2.getName() == "Father" && mother_son_inconsistency(remainders)){
		cout<<"Mother is left with son without father's presence."<<endl;
		return false;
	}
	// The thief cannot stay with any family member, if the policeman is not there.
	return Person::canGetOnTheRaftWith(p2, remainders);
}

// Polymorphic canGetOnTheRaftWith method for Policeman class
bool Policeman::canGetOnTheRaftWith(const Person& p2, const List& remainders) const{
	// The father cannot stay with any of the daughters, without their mother's presence.
	if (p2.getName() == "Mother" && father_daughter_inconsistency(remainders)){
		cout<<"Father is left with daughter without mother's presence."<<endl;
		return false;
	}
	// The mother cannot stay with any of the sons, without their father's presence.
	if (p2.getName() == "Father" && mother_son_inconsistency(remainders)){
		cout<<"Mother is left with son without father's presence."<<endl;
		return false;
	}
	// The thief cannot stay with any family member, if the policeman is not there.
	return Person::canGetOnTheRaftWith(p2, remainders);
}

// Polymorphic canGetOnTheRaftWith method for Thief class
bool Thief::canGetOnTheRaftWith(const Person& p2, const List& remainders) const{
	// The thief cannot get on the raft with anyone except the policeman.
	if (p2.getName() != "Policeman")
		return false;
	return true;
}
