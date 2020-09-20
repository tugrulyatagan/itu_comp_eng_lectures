/* 
 * File:   Traversal.h
 * Author: ovatman
 *
 * Created on April 28, 2010, 11:01 AM
 */

#ifndef _TRAVERSAL_H
#define	_TRAVERSAL_H

#include <iostream>
#include <string.h>

using namespace std;

class Graph;

//Traversal class is used to provide an abstraction for the graph traversal classes.
class Traversal{

		
    protected:
		int bufferCap;							//buffer capacity
        int visitedIndex;						//visited nodes Index
        string *visited;					//visited nodes buffer
        int toBvisitedIndex;					//future visit node index
        string *toBvisited;					//future visit node buffer

        virtual void flush();					//reset the buffers
		virtual bool contains(string*,string);	//check if a buffer contains a value


    public:

        virtual string traverse(const Graph&)=0;	//Traverse algorithm
        
        Traversal();								//Constructor
};

#endif	/* _TRAVERSAL_H */

