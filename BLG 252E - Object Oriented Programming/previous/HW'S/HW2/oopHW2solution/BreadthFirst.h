/* 
 * File:   BreadthFirst.h
 * Author: ovatman
 *
 * Created on April 28, 2010, 11:16 AM
 */

#ifndef _BREADTHFIRST_H
#define	_BREADTHFIRST_H

#include <iostream>
#include <string.h>

using namespace std;

#include "Traversal.h"
#include "Graph.h"
#include "Node.h"

//Breadth first traverser class 
class BreadthFirst:public Traversal{

    public:
        BreadthFirst():Traversal(){};			
        string traverse(const Graph&);		//Traverser method
};

#endif	/* _BREADTHFIRST_H */

