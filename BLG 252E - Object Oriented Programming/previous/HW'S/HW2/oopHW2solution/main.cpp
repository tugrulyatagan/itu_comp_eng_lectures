#include <iostream>
#include <string>

using namespace std;

#include "Node.h"
#include "Graph.h"
#include "Directed.h"
#include "Tree.h"
#include "BreadthFirst.h"
#include "DepthFirst.h"

int Graph::nOfGraphs=0;

int main(int argc, char** argv)
{
    
    Graph* aGraph= new Graph();
    DirectedGraph* bGraph= new DirectedGraph();
    Tree* cGraph= new Tree();

    aGraph->addNode("A");
    aGraph->addNode("B");
    aGraph->addNode("C");

    aGraph->addEdge("B","A");
    aGraph->addEdge("A","C");
    aGraph->addEdge("C","B");

    bGraph->addNode("A");
    bGraph->addNode("B");
    bGraph->addNode("C");

    bGraph->addEdge("B","A");
    bGraph->addEdge("A","C");
    bGraph->addEdge("C","B");

    cGraph->addNode("A");
    cGraph->addNode("B");
    cGraph->addNode("C");
    cGraph->addNode("D");
    cGraph->addNode("E");

    cGraph->addChild("A","B");
    cGraph->addChild("A","C");
    cGraph->addChild("B","D");
    cGraph->addChild("C","E");


    aGraph->unite(*bGraph);
    //cGraph->addEdge("A","B"); //Compiler error

    //bGraph->unite(*cGraph); //Compiler error

    //cGraph->intersect(*aGraph); //Compiler error

    Graph** someGraphs= new Graph*[3];

    someGraphs[0]=aGraph;

    someGraphs[1]=bGraph;

    someGraphs[2]=cGraph;

    for(int i=0;i<3;i++)
        someGraphs[i]->acceptTraverse(new BreadthFirst()); 

    someGraphs[0]->acceptTraverse(new DepthFirst()); 

    someGraphs[1]->acceptTraverse(new DepthFirst()); 

    someGraphs[2]->acceptTraverse(new DepthFirst()); 

    return 0;

}




