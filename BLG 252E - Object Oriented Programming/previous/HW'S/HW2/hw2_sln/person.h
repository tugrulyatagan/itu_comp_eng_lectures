#ifndef PERSON_H_
#define PERSON_H_

#include <list>
#include <string>
using namespace std;

// a list of strings and a const iterator just for moving on the list
typedef list<string> List;
typedef List::const_iterator Iter;


// Decleration of necessary functions to avoid repetition as much as possible
//__________________________________________________________________________________

// to check if a person whose name is given in the list or not
bool is_in_list(const List&, string);
//to check for inconsistencies among remainders with respect to given rules
bool father_daughter_inconsistency(const List&);
bool mother_son_inconsistency(const List&);
bool thief_family_inconsistency(const List&);


// Decleration of necessary classes to avoid repetition as much as possible
//__________________________________________________________________________________

// Base class 
class Person{
protected:    // data attributes can be used directly from objects of inherited classes
	string name;					
public:
	Person(string given_name){name = given_name;}    // constructor to initialize name
	string getName() const{      // method to return the person's name
		return name;
	}
	virtual bool canOperateTheRaft() const = 0;  // pure virtual function
	virtual bool canGetOnTheRaftWith(const Person&, const List&) const;   // canGetOnTheRaftWith method of base class
};

// Operator and Passenger classes are inherited from Person class
// They differ in their ability of operating the raft or not
class Operator: public Person {
public:
	Operator(string given_name):Person(given_name){}  // constructor calling the base class constructor
	bool canOperateTheRaft() const {return true;}     // objects inherited from this class can operate the raft
};
class Passenger: public Person {
public:
	Passenger(string given_name):Person(given_name){}  // constructor calling the base class constructor
	bool canOperateTheRaft() const {return false;}     // objects inherited from this class cannot operate the raft
};


// Mother, Father and Policeman classes are inherited from Operator class
// They differ in their canGetOnTheRaftWith method
class Mother: public Operator{
public: 
	Mother(string given_name):Operator(given_name){}   // constructor calling the base class constructor
	bool canGetOnTheRaftWith(const Person&, const List&) const; 
};
class Father: public Operator{
public: 
	Father(string given_name):Operator(given_name){}   // constructor calling the base class constructor
	bool canGetOnTheRaftWith(const Person&, const List&) const; 
};
class Policeman: public Operator{
public: 
	Policeman(string given_name):Operator(given_name){}   // constructor calling the base class constructor
	bool canGetOnTheRaftWith(const Person&, const List&) const; 
};
// Daughter, Son and Thief classes are inherited from Passenger class
// They differ in their canGetOnTheRaftWith method
class Daughter: public Passenger{
public: 
	Daughter(string given_name):Passenger(given_name){}   // constructor calling the base class constructor
	bool canGetOnTheRaftWith(const Person&, const List&) const; 
};
class Son: public Passenger{
public: 
	Son(string given_name):Passenger(given_name){}   // constructor calling the base class constructor
	bool canGetOnTheRaftWith(const Person&, const List&) const; 
};
class Thief: public Passenger{
public: 
	Thief(string given_name):Passenger(given_name){}   // constructor calling the base class constructor
	bool canGetOnTheRaftWith(const Person&, const List&) const; 
};

#endif
