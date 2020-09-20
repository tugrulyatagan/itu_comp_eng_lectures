#include "DepthFirst.h"

//Depth first traverser method
string DepthFirst::traverse(const Graph& aGraph){

    Graph* g=(const_cast <Graph*> (&aGraph));

    flush();				//Flush the buffers
    
    string result=" DFT: ";

	//If the graph accepts depth first traversal
	
    if(g->acceptsDF()){
        Node* curNode=g->getNode(0);		//Get the initial node from the graph

        visit(curNode,g);					//Visit each node recursively

		//Construct the result
        for(int i=0;i<visitedIndex;i++)
            result=result+visited[i]+"-";

        return result;
    }

    else return "Depth First Traversal is not allowed on directed graphs!!";
}

//Recursive function to visit each node in th graph.
void DepthFirst::visit(Node* aNode,Graph* g){
	//put the current visited node to the visited list
    visited[visitedIndex++]=aNode->getNodeName();

	//Visit its childs recursively if they haven't already been visited.
    for(int i=0;i<aNode->getNumOfAdjacents();i++)
        if(!contains(visited,aNode->getAdjacent(i)))
            visit(g->getNode(aNode->getAdjacent(i)),g);
}
