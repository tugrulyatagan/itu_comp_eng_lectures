#include "BreadthFirst.h"

//Traverse the graph in the <par> using Breadth first traversal algorithm
string BreadthFirst::traverse(const Graph& aGraph){
    Graph* g=(const_cast <Graph*> (&aGraph));

    int nofNodes=g->getNumOfNodes();
    int visitingIndex=0;
    string result=" BFT: ";

    flush();					//Flush the buffers
		
    Node* curNode=g->getNode(0);	//Start from the initial node

    do{													//Search until...
		//Put the current node in visited list 
        visited[visitedIndex++]=curNode->getNodeName();

		//put all its childs in "to be visited" list if they haven't been already listed as "visited" or "to be visited"
        for(int i=0;i<curNode->getNumOfAdjacents();i++)
            if(!contains(toBvisited,curNode->getAdjacent(i)) && !contains(visited,curNode->getAdjacent(i)))
                toBvisited[toBvisitedIndex++]=curNode->getAdjacent(i);

		//get the next node "to be visited"
        curNode=g->getNode(toBvisited[visitingIndex++]);

    }while(toBvisited[visitingIndex-1]!="");		//...no more nodes left to be visited

	//Construct the result
    for(int i=0;i<visitingIndex;i++)
        result=result+visited[i]+"-";

    return result;
}
