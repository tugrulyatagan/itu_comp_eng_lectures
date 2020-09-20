/* 
 * File:   DepthFirst.h
 * Author: ovatman
 *
 * Created on April 28, 2010, 11:16 AM
 */

#ifndef _DEPTHFIRST_H
#define	_DEPTHFIRST_H

#include "Traversal.h"
#include "Graph.h"
#include "Node.h"

//DepthFirst class is used to traverse graphs using depth first algorithm
class DepthFirst:public Traversal{

    private:
        void visit(Node *,Graph *);			//Recursive function to visit nodes during traversal
        
    public:
        DepthFirst():Traversal(){};		
        string traverse(const Graph&);		//traverser method

};

#endif	/* _DEPTHFIRST_H */

