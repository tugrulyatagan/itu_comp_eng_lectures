#include <iostream>
#include <string>

using namespace std;

#include "Node.h"
#include "Graph.h"

int Graph::nOfGraphs=0;

int main(int argc, char** argv)
{
    Graph* aGraph= new Graph("aGraph.txt");

    cout<<aGraph->toString()<<endl;

    Graph bGraph;

    bGraph.addNode("A");

    bGraph.addNode("B");

    bGraph.addNode("D");

    bGraph.addEdge("A","B");

    bGraph.addEdge("A","D");

    aGraph->unite(bGraph);

    cout<<aGraph->toString()<<endl;

    aGraph->deleteNode("B");

    aGraph->deleteEdge("A","C");

    cout<<aGraph->toString()<<endl;

    aGraph->intersect(bGraph);

    cout<<aGraph->toString()<<endl;

    Graph* cGraph=new Graph(bGraph);

    cGraph->deleteNode("D");

    Graph dGraph(3);

    dGraph.intersect(*cGraph);

    cout<<dGraph.toString()<<endl;

    delete aGraph;
    delete cGraph;
    
    return 0;

}


