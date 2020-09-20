#include <iostream>
#include <vector>
#include <algorithm>    // std::unique, std::distance
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

#define DEBUG_MODE 1

using namespace std;

int totalReceivedPacketNumber = 0;
int totalGeneratedPacketNumber = 0;

class Packet{
  public:
	Packet();
	Packet(int, int);
	int hop;
	int fromNode;
};

Packet::Packet(){

}

Packet::Packet(int hopCount, int from){
	hop = hopCount;
	fromNode = from;
}

//************************ Node
class Node {
public:
	Node(Node **, int, int);
	~Node();
	bool isFull();
	bool isNeighboor(int);
	void sendPacketToNode(int, int);
	void getPacket(int,int);
	void checkDuplicatePackets();
	void processIncomingPackets(int);
	Node **parentGraph;
	vector<int> neighboorNodes;
	vector<Packet> incomingPacket;
	int nodeID;
	int maxNodeDegree;
	int receivedPacketNumber;
	int generatedPacketNumber;
	bool isTraversed;
};

Node::Node(Node **relatedGraph, int ID, int nodeDegree) {
	parentGraph = relatedGraph;
	nodeID = ID;
	maxNodeDegree = nodeDegree;
	receivedPacketNumber = 0;
	generatedPacketNumber = 0;
	isTraversed = false;
}

bool Node::isNeighboor(int found) {
	if (neighboorNodes.empty()) {
		return false;
	}
	for (int i = 0; i < maxNodeDegree; i++) {
		if (neighboorNodes[i] == found) {
			return true;
		}
	}
	return false;
}

bool Node::isFull() {
	int s = neighboorNodes.size();
	return s == maxNodeDegree;
}

Node::~Node() {

}

void Node::processIncomingPackets(int currentHop) {
	checkDuplicatePackets();

	int currentIndex;
	for (currentIndex = 0; currentIndex < incomingPacket.size(); currentIndex++){
		if(incomingPacket[currentIndex].hop == currentHop){
			break;
		}
	}
	if (currentIndex !=  incomingPacket.size()){
		Packet p = incomingPacket[currentIndex];
		incomingPacket.erase(incomingPacket.begin()+currentIndex);

		generatedPacketNumber++;
		totalGeneratedPacketNumber++;

		for (int i = 0; i < neighboorNodes.size(); i++) {
			if(neighboorNodes[i] != p.fromNode) {
				sendPacketToNode(neighboorNodes[i], p.hop-1); // -1 for decrease
			}
		}
	}
}

void Node::sendPacketToNode(int targetNodeID, int hop) {
#if DEBUG_MODE
	cout << nodeID << " sent to " << targetNodeID << " (hop: " << hop << ")" << endl;
#endif
	parentGraph[targetNodeID]->receivedPacketNumber++;
	totalReceivedPacketNumber++;
	parentGraph[targetNodeID]->getPacket(nodeID,hop);
}


void Node::getPacket(int from, int hop) {
	Packet p(hop,from);
	incomingPacket.push_back(p);
}

bool compareBigger (Packet a, Packet b) {
	return (a.hop < b.hop);
}

bool compareEqual (Packet a, Packet b) {
	return (a.hop == b.hop);
}

void Node::checkDuplicatePackets(){
	sort(incomingPacket.begin(), incomingPacket.end(),compareBigger);
	vector<Packet>::iterator it;
	it = unique (incomingPacket.begin(), incomingPacket.end(), compareEqual);
	incomingPacket.resize(distance(incomingPacket.begin(),it));
	unique(incomingPacket.begin(), incomingPacket.end(), compareEqual);
}

//************************ Graph
class Graph {
private:
	void createGraph();
	void incrementSuitableDegree();
	void traverseGraph(int);
	void checkConnected();
	void reconnectGraph();
	Node **graph;
	int N;
public:
	Graph(int);
	~Graph();
	void printGraph();
	void startSimulation(int);
	void printResults();
};

Graph::Graph(int size) {
	N = size;
	graph = new Node*[N];
	for (int i = 0; i < N; i++) {
		graph[i] = new Node(graph, i, (rand() % 3) + 2);
	}
	createGraph();
	checkConnected();
}

Graph::~Graph() {
	delete[] graph;
}

void Graph::createGraph() {
	for (int i = 0; i < N; i++) {
		while (graph[i]->neighboorNodes.size() < graph[i]->maxNodeDegree) {
			int randomNode = rand() % N;
			int infiniteLoopCounter = 0;
			while ((randomNode == i) || (graph[randomNode]->isFull()) || (graph[i]->isNeighboor(randomNode))) {
				randomNode = (randomNode + 1) % N;
				if (infiniteLoopCounter++ > N) {
					incrementSuitableDegree();
					infiniteLoopCounter = 0;
				}
			}
			graph[i]->neighboorNodes.push_back(randomNode);
			graph[randomNode]->neighboorNodes.push_back(i);
		}
	}
}

void Graph::incrementSuitableDegree() {
	for (int i = 0; i < N; i++) {
		if (graph[i]->maxNodeDegree < 4) {
			graph[i]->maxNodeDegree++;
			return;
		}
	}
}

void Graph::checkConnected() {
	traverseGraph(0);
	for (int k = 0; k < N; k++) {
		if (graph[k]->isTraversed == false) {
			reconnectGraph();
		}
	}
}

void Graph::traverseGraph(int id) {
	graph[id]->isTraversed = true;
	for (int i = 0; i < graph[id]->maxNodeDegree; i++) {
		if (graph[graph[id]->neighboorNodes[i]]->isTraversed == false) {
			traverseGraph(graph[id]->neighboorNodes[i]);
		}
	}
}

void Graph::reconnectGraph() {
	for (int k = 0; k < N; k++) {
		graph[k]->neighboorNodes.clear();
		graph[k]->isTraversed = false;
	}
	createGraph();
	checkConnected();
}

void Graph::printGraph() {
	cout << "GRAPH" << endl << "-----" << endl;
	for (int k = 0; k < N; k++) {
		for (int l = 0; l < graph[k]->neighboorNodes.size(); l++) {
			cout << k << " connected " << graph[k]->neighboorNodes[l] << endl;
		}
		cout << endl;
	}
}

void Graph::startSimulation(int maxHopCount) {
#if DEBUG_MODE
	cout << endl << "SIMULATION" << endl << "----------" << endl;
#endif
	graph[0]->getPacket(-1,maxHopCount);
	for (int h = maxHopCount; h > 0; h--) {
		for (int k = 0; k < N; k++) {
			graph[k]->processIncomingPackets(h);
		}
	}
}

void Graph::printResults() {
	cout << endl << "RESULTS" << endl << "-------" << endl;
	for (int k = 0; k < N; k++) {
		cout << "Node " << k << endl;
		cout << "Received packet numbers: " << graph[k]->receivedPacketNumber << endl;
		cout << "Generated packet numbers: " << graph[k]->generatedPacketNumber << endl << endl;
	}
	cout << endl << "TOTAL RESULTS" << endl << "-------" << endl;
	cout << "Total received packet number: " << totalReceivedPacketNumber << endl;
	cout << "Total generated packet number: " << totalGeneratedPacketNumber << endl << endl;
}

int main(int argc, char *argv[]) {
	if (argc != 3) {
		cout << "Invalid arguments!" << endl;
		return -1;
	}
	srand(time(NULL));

	int graphSize = atoi(argv[1]);
	int maxHopCount = atoi(argv[2]);

	cout << "Network size: " << graphSize << endl;
	cout << "Hop count: " << maxHopCount << endl << endl;

	Graph g(graphSize);
	g.printGraph();
	g.startSimulation(maxHopCount);
	g.printResults();

	cout << "Program terminated successfully!" << endl;
	return 0;
}
