#include "Graph.h"
#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

int Graph::graphCount=0;

int main()
{ 
     Graph bGraph;
     Graph aGraph;
	 aGraph.newNode("A");
     aGraph.newNode("F");
     aGraph.newNode("G");
     aGraph.newEdge("A","F");
	 aGraph.printGraph();
	 bGraph.newNode("A");
     bGraph.newNode("B");
     bGraph.newNode("D");
     bGraph.newEdge("A","B");
     bGraph.newEdge("A","D");
	 bGraph.printGraph();
     aGraph.unite(bGraph);
     bGraph.deleteNode("B");
     bGraph.deleteEdge("A","C");
	 aGraph.intersect(bGraph);
	return EXIT_SUCCESS;
}

