#include "Graph.h"
#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

Node::Node(string nodename){
	name=nodename;
	adjacent=NULL;
	numEdges=0;
}

Node::Node(){
	adjacent=NULL;
	numEdges=0;
}

string Node::getName(){
	return name;
}

Node::Node(const Node &copy){
	cout << "Enter your copy node name: ";
	cin >> name;
	adjacent=copy.adjacent;
	numEdges=copy.numEdges;
}

bool Node::addAdjacent(const Node &newadjacent){
		int i=0;
		Node** temp = new Node*[++numEdges];//komsu sayisinin bir fazlasi yer al

		for(i = 0 ; i < numEdges-1 ; i++) 
			temp[i] = adjacent[i];//komsulari geciciye at

		temp[i] = const_cast <Node *>(&newadjacent);//yeni komsuyu geciciye ekle
		adjacent = new Node*[numEdges];
		
		for(i = 0 ; i < numEdges ; i++)
			adjacent[i] = temp[i];//geciciyi komsuya at

		delete []temp;
		return true;
}

bool Node::delAdjacent(string deladjacent){
		int i=0,j=0;
		Node** temp = new Node*[--numEdges];//komsu sayisinin bir eksigi yer al

		for(i = 0; i < numEdges+1; i++){		
			if(deladjacent==adjacent[i]->getName())
				continue;
						
			else{
				temp[j]=adjacent[i];
				j++;
			}
		}
		
		adjacent = new Node*[numEdges];
		
		for(i = 0 ; i < numEdges ; i++) 
			adjacent[i] = temp[i];//komsulari geciciye at
		
		delete []temp;
		return true;
}

Node** Node::getAdjacents(){
	return adjacent;//komsularini dondur
}

Node::~Node(){
	delete []adjacent;//komsulari kaldir
}
