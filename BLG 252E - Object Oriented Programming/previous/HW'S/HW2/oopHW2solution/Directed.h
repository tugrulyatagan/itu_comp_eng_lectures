#ifndef _DIRECTED_H
#define	_DIRECTED_H

#include <iostream>
#include <string.h>
#include <fstream>
using namespace std;

#include "Graph.h"
#include "BreadthFirst.h"
#include "DepthFirst.h"

class DirectedGraph : public Graph{

    public:

        DirectedGraph(){};                              //Constructors and destructor
        DirectedGraph(int){};
        DirectedGraph(string graphFile):Graph(graphFile){};
        DirectedGraph(const DirectedGraph &){};
        ~DirectedGraph(){};

        bool addEdge(string,string);          			//add an edge to the graph
        bool deleteEdge(string,string);       			//delete an edge from the graph
        void intersect(const DirectedGraph&);         	//intersect the graph with the <par>
        void unite(const DirectedGraph&);             	//intersect the graph with the <par>

        void acceptTraverse(Traversal*);				//Accept traversal in the <par>
        bool acceptsDF();								//Query if the directed graph accepts DF traversal					
};

#endif	/* _DIRECTED_H */

