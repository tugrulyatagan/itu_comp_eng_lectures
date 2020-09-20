/*
*
* BLG252E
* 2011 Spring
* 2nd Homework
*
*/
/*
*
* Student Name: Abdullah AYDEÐER
* Student ID : 040090533
*
*/

#ifndef Person_H
#define Person_H
#include <iostream>
#include <list>    // to be able to use STL list
#include <string>
using namespace std;

// a list of strings and an iterator to be able to move on the list
typedef list<string> List;
typedef List::const_iterator Iter; // const_iterator is used to move on const List

class Person{		//Base class
	protected:
		string name;		//Same for all derived class
	public:
		string  getName() const { return name;}		//function for returning name is same for all derived class
		Person(const string new_name){ name = new_name; }	//constructor assigns input parameter to name
		virtual bool canOperateTheRaft ()const { return false; };	//virtual function works different for each derived class
		virtual bool canGetOnTheRaftWith (const Person &,const List &) const { return false; };	
		virtual char* getCharacter() const { return ""; };	//return the char array
};

class Mother:public Person{
	public:	
		Mother(string new_name):Person(new_name){};		//construct only calls Person's class construct
	private:
		bool canOperateTheRaft ()const { return true; }		//
		bool canGetOnTheRaftWith (const Person &,const List &)const;
		char* getCharacter() const { return "Mother"; }	//return the char array(Here is Mother)
};

class Father:public Person{
	public:
		Father(string new_name):Person(new_name){};		
	private:
		bool canOperateTheRaft ()const { return true; }
		bool canGetOnTheRaftWith (const Person&,const List&) const;
		char* getCharacter() const { return "Father"; }		//return the char array(Here is Father)
};

class Daughter:public Person{
	public:
		Daughter(string new_name):Person(new_name){};		
	private:
		bool canOperateTheRaft ()const { return false; }
		bool canGetOnTheRaftWith (const Person &,const List &)const ;
		char* getCharacter() const { return "Daughter"; }		//return the char array(Here is Daughter)
};

class Son:public Person{
	public:
		Son(string new_name):Person(new_name){};	
	private:
		bool canOperateTheRaft ()const { return false; }
		bool canGetOnTheRaftWith (const Person &,const List &) const;
		char* getCharacter() const { return "Son"; }		//return the char array(Here is Son)
};

class Thief:public Person{
	public:
		Thief(string new_name):Person(new_name){};		
	private:
		bool canOperateTheRaft ()const { return false; }
		bool canGetOnTheRaftWith (const Person &,const List &)const;
		char* getCharacter() const { return "Thief"; }		//return the char array(Here is Thief)
};

class Policeman:public Person{
	public:
		Policeman(string new_name):Person(new_name){};		
	private:
		bool canOperateTheRaft ()const { return true; }
		bool canGetOnTheRaftWith (const Person &,const List &)const ;
		char* getCharacter() const { return "Policeman"; }		//return the char array(Here is Policeman)
};

#endif