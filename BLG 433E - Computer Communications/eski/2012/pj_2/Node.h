/****************************************************************
*	Name Surname		: Abdullah AYDEÐER						*
*   Number				: 040090533								*
*	University			: Istanbul Technical University			*
*	Lecture				: Computer Communications				*
*	Lecturer			: Sema OKTUG							*
*	Project Number		: 2										*
*	Created Date		: 25.12.2012							*
*	Purpose of class	: Keeping nodes' information and		*
*							implementing neccessary functions	*
*****************************************************************/
#ifndef NODE_H
#define NODE_H	//define node header once

#include <iostream>
#include <string>
#include <queue>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <list>
#include "Link.h"
#include "Triple.h"

#define MAXCOST 10
#define MAXROUTE MAXCOST*9999	//this will adjust routing of all nodes to 99999(like infinity)

using namespace std;

class Node{
	public:
		Node(){	}
		int num;
		int *isAdded;
		list<Link> connectedNodes;	
		vector<Pair> routingTable;		//pair.num1 = which node is the way, pair.num2 = cost
		void initialize(int, int);
		void clearRouting(int );
		void clearIsAdded(int );
		void displayRouting();
		void displayNodes(Node *, int);
		void connectNeighbours(Node *, list<Pair>);
		Triple createRandomLinks(Node *, int);
};

#endif

