/* 
 * File:   Tree.h
 * Author: ovatman
 *
 * Created on April 28, 2010, 10:40 AM
 */

#ifndef _TREE_H
#define	_TREE_H

#include <iostream>
#include <string.h>
#include <fstream>
using namespace std;

#include "Graph.h"

class Tree : public Graph{

    private:
        bool addEdge(){};
        bool deleteEdge(){};
    public:

        Tree(){};                              //Constructors and destructor
        Tree(int){};
        Tree(string graphFile):Graph(graphFile){};
        Tree(const Tree &){};
        ~Tree(){};

        bool addChild(string,string);          	//add an edge to the graph
        bool deleteChild(string,string);       	//delete an edge from the graph
        void intersect(const Tree&);         	//intersect the graph with the <par>
        void unite(const Tree&);             	//intersect the graph with the <par>

        void acceptTraverse(Traversal*);		//Accept the traversal in the <par>
};

#endif	/* _TREE_H */

