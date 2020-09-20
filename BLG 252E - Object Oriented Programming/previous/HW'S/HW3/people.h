/*
*
* BLG252E
* 2011 Spring
* 3rd Homework
*
*
*
*
* Student Name: ABDULLAH AYDEÐER
* Student ID : 040090533
*
*
*/
#ifndef PEOPLE_H
#define PEOPLE_H
#include <iostream>
#include <string>

using namespace std;

class Person{		//Base class for all people
	protected:
		int id;			//All people have id (in my design)
		string name;	//All people absolutely have name
		string place;	//All people should hold their place (right or left)
	public:
		Person(){ name=" "; id = -1; };		
		Person(string );
		int getID() const;
		string getName() const;
		void setPlace(string );
		string getPlace()const;
		virtual bool canGetOnTheRaftWith(const Person &) const { cout<<"\n\nPersondayýz\n\n";  return false;}	//This is virtual function since all Operators have these function 
};

class Operator:public Person{
	protected:			//Does not need any protected or private members
	public:
		Operator(){};
		Operator(string );
		bool canGetOnTheRaftWith(const Person &) const { cout<<"\n\nOperatordeyizz\n\n";  return false;}
};

class NonOperator:public Person{
	protected:			//Does not need any protected or private members
	public:
		NonOperator(){};
		NonOperator(string );
};

class Father:public Operator{		//Does not need any protected or private members
	public:				
		Father(string );
		bool canGetOnTheRaftWith(const Person &) const;
};

class Mother:public Operator{		//Does not need any protected or private members
	public:				
		Mother(string );
		bool canGetOnTheRaftWith(const Person &) const;
};

class Police:public Operator{		//Does not need any protected or private members
	public:				
		Police(string );
		bool canGetOnTheRaftWith(const Person &) const;
};

//NonOperators inherited class only have constructor in their class
class Son:public NonOperator{		
	public:				
		Son(string );
};

class Daughter:public NonOperator{		
	public:
		Daughter(string );
};

class Thief:public NonOperator{			
	public:
		Thief(string );		
};

#endif