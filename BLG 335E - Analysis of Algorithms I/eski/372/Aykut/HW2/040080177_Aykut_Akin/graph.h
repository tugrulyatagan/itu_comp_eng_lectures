/********************************************************************************
*	Name Surname: Aykut Akin													*
*	Number		: 040080177														*
*	Due Date	: 23.03.2011													*
*																				*
*	Every information about functions and classes can be found in report		*
*																				*
*********************************************************************************/

#ifndef __GRAPH_H__
#define __GRAPH_H__

#include "edge.h"
#include <vector>

using namespace std;

class Graph{
	
		vector<Edge*> edges;
		vector<Edge*> mst;

		int m; //node number
		int n; //edge number
		int totalmst; //minimum weight
		int total;//weight

		void readData(string fileName);

	public:
		Graph(string fileName);
		~Graph();

		void kruskal();
		void writeData(int time);
		void clear();
};

#endif