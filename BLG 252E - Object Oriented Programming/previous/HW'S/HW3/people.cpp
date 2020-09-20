#include "people.h"

Person::Person(string newname){
	name = newname;
	place = "left";
}

void Person::setPlace(string p){
	place = p;
}

int Person::getID() const{
	return id;
}

string Person::getPlace() const{
	return place;
}

string Person::getName() const{
	return name;
}

Operator::Operator(string newname):Person(newname){};

NonOperator::NonOperator(string newname):Person(newname){};

Father::Father(string newname):Operator(newname){id=0;};

Mother::Mother(string newname):Operator(newname){id=1;};

Police::Police(string newname):Operator(newname){id=2;};

Son::Son(string newname):NonOperator(newname){id=3;};

Daughter::Daughter(string newname):NonOperator(newname){id=4;};

Thief::Thief(string newname):NonOperator(newname){id=5;};

bool Father::canGetOnTheRaftWith(const Person &p)const{
	
	if(p.getID()!= 4 && p.getID()!=5)	//If not daughter and not thief
			return true;
	else{
		if( p.getID()== 4)	//If daughter
			throw "Father-Daughter Inconsistency";
		else		//If thief
			throw "Thief-Family Inconsistency";
	}
}

bool Mother::canGetOnTheRaftWith(const Person &p)const{
	if(p.getID()!= 3 && p.getID()!= 5)	//If not son and not thief
		return true; 
	else{	
		if( p.getID()==5 )	//If son
			throw "Mother-Son Inconsistency";
		else		//If thief
			throw "Thief-Family Inconsistency";	
	}
}

bool Police::canGetOnTheRaftWith(const Person &p) const{
	return true;	//Police can get on the raft with all people
};


