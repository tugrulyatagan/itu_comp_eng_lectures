#ifndef __NODE_H__
#define __NODE_H__

#include <iostream>
#include <string>
using namespace std;

class Node{

     private:
          string name;                          //Node name
          Node** adjacents;                     //Adjacent nodes
          int nofAdjacents;                     //Number of adj.
          int containsAdjacent(string);         //If contains adjacent in <par> return its indice

     public:
          Node();                               //Constructors and destructors
          Node(string);                         
          Node(const Node &);
          ~Node();

          string getNodeName();                 //Get name of a node
          string toString();                    //Get string representation of Node
          string getAdjacent(int);              //Get adjacent at <par>
          bool addAdjacent(const Node&);        //add an adjacent node
          bool deleteAdjacent(const Node&);     //delete an adjacent
          void intersect(const Node&);          //Intersect node adjacents with the node in the <par>
          void unite(const Node&);              //Unite node adjacents with the node in the <par>
          int getNumOfAdjacents();
};

#endif
