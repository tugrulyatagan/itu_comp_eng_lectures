/************************************************************
*	Name Surname		: Abdullah AYDEÐER					*
*   Number				: 040090533							*
*	Lecture				: Analysis of Algorithms			*
*	Lecturer			: Zehra ÇATALTEPE					*
*	Project Number		: 1									*
*	Due Date			: 02.04.2012						*
*************************************************************/
#ifndef COMPNODE_H
#define COMPNODE_H	//define compnode once

#include <iostream>
#include <string>
#include <list>
#include <queue>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

class CompNode{

	private:
		bool discovered;	//for Breath First Search in function makeAllinfected  
		int num;	//number of computer
		int time;	//time of computer to communicate(time of Computer Node)
		bool travelled;			//Special variable for determining virus path, using in isInfected function
		bool infected;		//computer with 'num' number has been virused on time='time' 
	public:
		list<CompNode*> others;		//Computer communication lists
		list<CompNode*> neighbour;	//Computer Nodes with same number, different times
										//These lists must be public so that from functions in main can be accessible
		
		int getNum();	//get method for 'num'
		int getTime();	//get method for 'time'
		bool getInfected();	//get method for 'infected'
		bool getTravelled();	//get method for 'travelled'
		void setTravelled(bool );	//set method for 'travelled'

		CompNode();		//default constructor
		CompNode(int, int);	//constructor with number and time parameters

		static void addToALL(list<CompNode*> *ALL, CompNode *cp){
			/****************************************************************************************************
			*	Function Name		: addToALL																	*
			*	Aim to be written	: Adding given computer node to the list of all nodes						*
			*	Parameters			: pointer of list of all computers(ALL) and one pointer of a computer node	*
			*	Return value		: --																		*
			*****************************************************************************************************/
			ALL->insert(ALL->end(), cp);		//Adding new node to the end of the list
		}

		static list<CompNode *> isExist(list<CompNode*> ALL, int searchNum){
			/****************************************************************************************************************************
			*	Function Name		: isExist																							*
			*	Aim to be written	: Determining the given num(searchNum) has to be added to the list of all nodes before or not		*
			*	Parameters			: pointer of list of all computers(ALL) and one integer(searchNum) of computer node for searching	*
			*	Return value		: pointer list of all found nodes																	*
			*****************************************************************************************************************************/
			list<CompNode *>::iterator it;	//iterator for travelling in the list
			list<CompNode *> found;		//list for holding finding nodes
			 for (it=ALL.begin(); it!=ALL.end(); it++){		//for all nodes in the ALL list
				if((*it)->getNum() == searchNum)	//if the numbers are equal
					found.insert(found.begin(), *it);	//then, add to the 'found' list
			}
			return found;
		}

		static void addNeighbour(list<CompNode *> cp1, CompNode *cp2){
			/************************************************************************************************
			*	Function Name		: addNeighbour															*
			*	Aim to be written	: Adding an edge between given node and each of the given lists' nodes	*
			*	Parameters			: 1 pointer list of computer nodes and one pointer of computer node		*
			*	Return value		: --																	*
			*************************************************************************************************/
			list<CompNode *>::iterator it;	//iterator for travelling in the list
			for(it = (cp1).begin(); it!= (cp1).end(); it++){	//For all elements in the cp1 list
				if( (*it)->getTime() < cp2->getTime()) 
					(*it)->neighbour.insert((*it)->neighbour.end(), cp2);	//Add new neighbour to the end of neighbour list
			}
		}

		static void makeTheyConnected(CompNode *cp1, CompNode *cp2){		
			/********************************************************************************
			*	Function Name		: makeTheyConnected										*
			*	Aim to be written	: Making an edge between given parameter nodes			*
			*	Parameters			: 2 pointers of computer nodes(cp1, cp2)				*
			*	Return value		: --													*
			*********************************************************************************/
			cp1->others.insert(cp1->others.begin(), cp2);	//an edge from cp1 to cp2
			cp2->others.insert(cp2->others.begin(), cp1);	//an edge from cp2 to cp1
		}

		static void virusInfected(int searchNum, int time, list<CompNode*> *ALL){
			/****************************************************************************************************************
			*	Function Name		: virusInfected																			*
			*	Aim to be written	: Making infected to the computer which num&time is given 								*
			*	Parameters			: pointer of list of all computers(ALL) and 2 integers for num(searchNum) and time		*
			*	Return value		: --																					*
			*****************************************************************************************************************/
			list<CompNode *>::iterator it;	//iterator for travelling in the list
			CompNode * goAllFromThis = NULL;	// holding the CompNode with num='searchNum' and time='time' with smallest time as possible	
			 for (it=ALL->begin(); it!=ALL->end(); it++){	//for all nodes
				if((*it)->getNum() == searchNum){	
					if(goAllFromThis){	//if any assignment has been done
						if(time <= (*it)->getTime() && (*it)->getTime() <= goAllFromThis->getTime()){	//if time is smaller than *it's time 
																								//and also smaller than 'goAllFromThis's time
								 (*it)->infected = true;	//make it infected
								 goAllFromThis = *it;
						}
					}
					else{	//if 'goAllFromThis' is still NULL
						if(time <= (*it)->getTime()){
							(*it)->infected = true;		//make it infected
							goAllFromThis = *it;	//assing *it to the 'goAllFromThis'
						}
					}
				}
			}
			if(goAllFromThis)		//if first virus does not effect any computer then return back
				makeAllInfected(&goAllFromThis);
			return;
		}

		static CompNode * getMyFirst(list<CompNode *> ALL, int searchNum){
			/****************************************************************************************************************************
			*	Function Name		: getMyFirst																						*
			*	Aim to be written	: Determining the node, that first time of all computers, has been infected with num ='searchNum'	*
			*	Parameters			: pointer of list of all computers(ALL) and one integer(searchNum) of computer node for searching	*
			*	Return value		: pointer list of all found nodes 																	*
			*****************************************************************************************************************************/
			list<CompNode *>::iterator it;		//iterator for travelling in the list
			CompNode *cp = NULL;	
			for(it = ALL.begin(); it != ALL.end(); it++){	//For all nodes in the ALL list
				if( cp ){ //if cp is not NULL
					if((*it)->getNum() == searchNum && (*it)->getTime() <= cp->getTime() && (*it)->infected == true )
						//That means if node has the same num value as searchNum and if it's time smaller than current node and if it has been infected
						cp = *it;
				}
				else{	//if cp is NULLL
					if((*it)->getNum() == searchNum && (*it)->infected == true )	//if num's are equal and node is infected
						cp = *it;	//assign *it to cp
				}
			}
			return cp;	//return back to the node with minumum time and num='searchNum'
		}

		static void makeAllInfected(CompNode **goALL){
			/********************************************************************************************************************************
			*	Function Name	  : makeAllinfected																							*
			*	Aim to be written : Applying Breath First Search from the given node(goALL) and making all nodes on the BFS path infected	*
			*	Parameters		  : pointer of the first infected node that will cause to the others infection								*
			*	Return value      : --																										*
			*********************************************************************************************************************************/
			queue<CompNode *> LAYER;	//queue for BFS 
			(*goALL)->discovered = true;	//make first element discovered's true 
			LAYER.push(*goALL);		//push first element to the queue
			list<CompNode *>::iterator iter;	
			CompNode *it;	//holding for popped node from queue
			while(!LAYER.empty()){
				it = LAYER.front();	//get element from queue
				LAYER.pop();	
					for(iter = (it)->neighbour.begin(); iter != (it)->neighbour.end(); iter++)	//for all possible edges between compnodes with same num
						if((*iter)->discovered == false){	//if it has not been discovered yet
							(*iter)->discovered = true;	//make it discovered
							(*iter)->infected = true;	//make it infected
							LAYER.push(*iter);	//add to the queue
						}
					for(iter = (it)->others.begin(); iter != (it)->others.end(); iter++)	//for all possible edges between different nodes
						if((*iter)->discovered == false){	//if it has not been discovered yet
							(*iter)->discovered = true;	//make it discovered
							(*iter)->infected = true;	//make it infected
							LAYER.push(*iter);	//add to the queue
						}
			}//end of while(search)
		}

}; //End of class parameters

int CompNode::getNum(){
	return num;
}
int CompNode::getTime(){
	return time;
}
bool CompNode::getInfected(){
	return infected;
}
bool CompNode::getTravelled(){
	return travelled;
}
void CompNode::setTravelled(bool travel){
	travelled = travel;
}

CompNode::CompNode(){
	travelled = true;
	discovered = false;
	infected = false;
}

CompNode::CompNode(int addNum, int addTime){
	num = addNum;
	time = addTime;
	discovered = false;
	infected = false;
}


#endif
