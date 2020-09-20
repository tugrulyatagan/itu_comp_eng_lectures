#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <iostream>
#include <string.h>
#include <fstream>
using namespace std;

class Graph{

     private:
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

          string getGraphName();                //Get graph name
          bool addNode(string);                 //add a node to the graph
          bool deleteNode(string);              //delete a node from the graph
          bool addEdge(string,string);          //add an edge to the graph
          bool deleteEdge(string,string);       //delete an edge from the graph
          void intersect(const Graph&);         //intersect the graph with the <par>
          void unite(const Graph&);             //intersect the graph with the <par>
          string toString();                    //get string representation of the graph
     };

#endif
