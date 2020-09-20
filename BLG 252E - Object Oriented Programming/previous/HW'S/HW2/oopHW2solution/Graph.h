#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <iostream>
#include <string.h>
#include <fstream>
using namespace std;

#include "Node.h"
#include "Traversal.h"
//class Traversal;

class Graph{
		
     protected:
          string name;                          //Graph name
          Node* nodes;                          //Nodes in the graph
          int nofNodes;                         //Number of nodes in the graph
          int containsNode(string);             //Query if a node is present
          string opBuf;                         //Operations buffer
          fstream* graphFile;                   //Graph's file
		  
		  
     public:
          static int nOfGraphs;                 //Number of graphs produced

          Graph();                              //Constructors and destructor
          Graph(int);
          Graph(string);
          Graph(const Graph &);
          ~Graph();

          string getGraphName();                		//Get graph name
          bool addNode(string);                 		//add a node to the graph
          bool deleteNode(string);              		//delete a node from the graph
          virtual bool addEdge(string,string);          //add an edge to the graph
          virtual bool deleteEdge(string,string);       //delete an edge from the graph
          virtual void intersect(const Graph&);         //intersect the graph with the <par>
          virtual void unite(const Graph&);             //intersect the graph with the <par>
          string toString();                    		//get string representation of the graph

          virtual void acceptTraverse(Traversal*);		//Accept the traversal in <par>
		  virtual bool acceptsDF();						//Query if the graph accepts DF traversal

          int getNumOfNodes();							//Get number of nodes in the graph
          Node* getNode(int);							//Get node numbered <par>
          Node* getNode(string);						//Get node named <par>
     };

#endif
