#include "Node.h"

void Node::initialize(int mynum, int numOfNodes){
	num = mynum;	
	isAdded = new int[numOfNodes];
	clearRouting(numOfNodes);
}

void Node::clearRouting(int numOfNodes){
	Pair p;
	p.num1 = -1; 
	p.num2 = MAXROUTE;
	routingTable.clear();
	for(int i=0; i<numOfNodes; i++){
		routingTable.push_back(p);
	}
	//clearIsAdded(numOfNodes);
}

void Node::clearIsAdded(int number){
	for(int i=0; i<number; i++){
		isAdded[i] = -1;
	}
}

void Node::displayRouting(){
	list<Link>::iterator it;
	cout << "Routing table of selected node:\n";
	for(int i=0; i<routingTable.size(); i++){
		if(routingTable[i].num2 == MAXROUTE)
			cout << "\tFor node: " << i << ": There is no path in the network(network is not connected!)" << endl;
		else
			cout << "\tFor node: " << i << ": " << routingTable[i].num1 << " with cost: " << routingTable[i].num2 << endl;
	}
}

void Node::displayNodes(Node *n, int randNode){
	list<Link>::iterator it;
	for(int i=0; i<randNode; i++){
		cout << "\n\nLinks of node" << i << ": " << endl;
		for(it = n[i].connectedNodes.begin(); it != n[i].connectedNodes.end(); it++){
			cout << "\tNode num:" << (*it).numberToLink << " Cost: " << (*it).cost << endl;
		}
	}
}

void Node::connectNeighbours(Node *n, list<Pair> p){
	list<Pair>::iterator it;
	Link linkToNodes;
	for(it = p.begin(); it != p.end(); it++){	
		linkToNodes.cost = (rand() %MAXCOST) +1;		//Path cost of 2-nodes is between 1 and MAXCOST which is defined at Node.h
		linkToNodes.numberToLink = (*it).num2;
		n[(*it).num1].connectedNodes.push_back(linkToNodes);
		it++;
		linkToNodes.numberToLink = (*it).num2;
		n[(*it).num1].connectedNodes.push_back(linkToNodes);
	}
}

Triple Node::createRandomLinks(Node *n, int maxNode){
	Triple p;
	int i1, i2;
	list<Link>::iterator it;
	bool found = false;
	
	while(!found){
		i1 = rand() % maxNode;
		i2 = rand() % maxNode;
		if(i1 != i2){
			for(it = n[i1].connectedNodes.begin(); it != n[i1].connectedNodes.end(); it++){	
				if((*it).numberToLink == i2){	
					found = true;
					p.num1 = i1;
					p.num2 = i2;
					p.cost = (*it).cost;
					n[i1].connectedNodes.erase(it);
					break;
				}
			}
		}
	}
	for(it = n[i2].connectedNodes.begin(); it != n[i2].connectedNodes.end(); it++){	
		if((*it).numberToLink == i1){
			n[i2].connectedNodes.erase(it);
			break;
		}
	}
	return p;
}