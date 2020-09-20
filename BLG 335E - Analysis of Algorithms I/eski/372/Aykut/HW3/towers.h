/********************************************************************************
*	Name Surname: Aykut Akin													*
*	Number		: 040080177														*
*	Due Date	: 09.05.2011													*
*																				*
*	Every information about functions and classes can be found in report		*
*																				*
*********************************************************************************/

#ifndef __TOWERS_H_
#define __TOWERS_H_

#include "blocks.h"
#include "graph.h"
#include "node.h"

class Towers{
	vector<Blocks*> towerList;
	vector<vector<int> > TopOrderedList;	
	vector<Graph*> graphList;
	vector<int> toporder(int);
	void readData(string);
public:
	Towers(string);
	void setGraphWithTopOrder();
	void getAnswers();
};

#endif