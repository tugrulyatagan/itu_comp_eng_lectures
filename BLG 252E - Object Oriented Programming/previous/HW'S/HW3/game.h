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
#ifndef GAME_H
#define GAME_H
#include "container.h"
#include "people.h"
#include <iostream>

using namespace std;

class Game{
	private:
		Container<Person> left,right;	//Containers hold people which are on the right and which are on the left
		int counter1,counter2;			//These are counters for recursion
		bool placer;					//placer determines the raft place
	public:
		Game();
		void addToLeft(Person );		//For add one Person to Left Container
		void addToRight(Person );		//For add one Person to Right Container
		Person takeFromLeft();			//Taking one Person from Left Container
		Person takeFromRight();			//Taking one Person from Right Container
		bool isFinished(Container<Operator>, Container<NonOperator> ) const;	//This function controls the game is finished or not
		bool sailAcrossFromLeftToRight(Person &, Person &);		
		//bool sailAcrossLeftToRight(Operator &);			//This function does not needed while solving the game
		bool sailAcrossFromRightToLeft(Person &, Person&);
		bool sailAcrossRightToLeft(Person &);
		bool isConsistency(Container<Person> &) const;		//This function controls all the inconsistencies
		bool isHere(int, Container<Person> ) const;			//This function helps the isConsistency function
		bool letsTry(Container<Operator> &, Container<NonOperator> &);	//This function is the base function for trying the solution
};
#endif