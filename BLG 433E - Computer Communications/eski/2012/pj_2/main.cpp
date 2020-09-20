#include "Packet.h"
#include "Recovery.h"
#include <math.h>

#define NUMBEROFLINKS 20
#define MINUMUMNODE 8
#define RANDOMNODE 4
#define MAXHOURS 40
#define FAILUREMEAN 2
#define RECOVERYMEAN 3
#define WAITFORPRINT 6	//wait for printing after failure or recovery (6 means 6*10 seconds = 1minute)

bool isAddedBefore(list<Pair> pairList, int x, int y){
	list<Pair>::iterator it, it2;
	for(it = pairList.begin(); it != pairList.end(); it++){	//for all nodes
		if((it)->num1 == x && (it)->num2 == y)	//if the current node is added before
			return true;
	}
	return false;
}

bool isAddedBeforeVector(vector<int> pairList, int x){
	list<Pair>::iterator it, it2;
	for(int i = 0; i < pairList.size(); i++){	//for all nodes
		if(pairList[i] == x)	//if the current node is infected
			return true;
	}
	return false;
}

list<int> findReachables(list<Pair> pairList, int x){
	list<Pair>::iterator it, it2;
	list<int> reachable;
	for(it = pairList.begin(); it != pairList.end(); it++){	//for all nodes
		if((it)->num1 == x)	//if the current node is infected
			reachable.push_back((it)->num2);
	}
	return reachable;
}

list<Pair> RandomizedNetwork(int maxNodeNumber){
	/*
		Creating random network according to given node-number
	*/
	int rand_x, rand_y;
	list<Pair> networkLinks;
	Pair p;

	while(networkLinks.size() != NUMBEROFLINKS * 2){
		rand_x = rand() % maxNodeNumber;
		rand_y = rand() % maxNodeNumber;
		while(rand_x == rand_y)
			rand_x = rand() % maxNodeNumber;
		p.num1 = rand_x;
		p.num2 = rand_y;
		if(!isAddedBefore(networkLinks, rand_x, rand_y)){	//if it is not added
			networkLinks.push_back(p);	//add it to network
			p.num2 = rand_x;
			p.num1 = rand_y;
			networkLinks.push_back(p);	//add reverse of it to network(since the links are bi-directional)
		}	
	}
	return networkLinks;
}

bool isConnected(list<Pair> pairList, int numberOfNodes){
	/*
		Checking the given pairs are connected or not
	*/
	vector<int> L, K;

	list<int> reach = findReachables(pairList, 0);
	list<int>::iterator it;

	for(it = reach.begin(); it != reach.end(); it++){	
		L.push_back(*it);
		K.push_back(*it);
	}
	int vertex;
	while(!K.empty()){
		vertex = K.back();
		K.pop_back();
		reach = findReachables(pairList, vertex);
		for(it = reach.begin(); it != reach.end(); it++){
			if(!isAddedBeforeVector(L, (*it))){	
				L.push_back(*it);
				K.push_back(*it);
			}
		}
	}
	if(L.size() == numberOfNodes){
		return true;
	}
	return false;
}

double generateRandomNumbers(int mean){
	/*
		Generating random number according to negative exponential distrubution with given mean value
	*/
	float a = rand();
	while( a > 1)
		a = a/10;

	double t;
	t = (-1) * (mean) * log(1-a);

	return t;
}

void insertProperOrder(vector<Recovery> *tN, Recovery rT){
	/*
		Inserting given Recovery to Recovery vector by increasing order
	*/
	int i;
	for(i=0; i<tN->size(); i++){
		if(rT.timeToRecover < (*tN)[i].timeToRecover)
			break;
	}
	tN->insert(tN->begin() + i, rT);
	return;
}

vector<double> createVectors(vector<Recovery> *recoveries){
	/*
		Creating random failure and recovery times up to MAXHOURS(defined at the beginning)
	*/
	double total_time = 0;
	double randTime;
	Recovery rec;
	vector<double> failures;
	int orderOfFail = 0;
	while(total_time < MAXHOURS){
		randTime = generateRandomNumbers(FAILUREMEAN);
		total_time += randTime;
		failures.insert(failures.end(), total_time);
		randTime = generateRandomNumbers(RECOVERYMEAN);
		total_time += randTime;
			rec.timeToRecover = total_time;
			rec.numberOfFailure = orderOfFail++;
			insertProperOrder(recoveries, rec);
		total_time -= randTime;
	}
	return failures;
}

int main(){
	srand ( time(NULL) );
	int randNode = rand() % RANDOMNODE;
	randNode += MINUMUMNODE;

	if(randNode+1> NUMBEROFLINKS || (randNode*(randNode-1))/2 < NUMBEROFLINKS){		//Invalid parameters
		cerr << "Number of links: " << NUMBEROFLINKS << " and number of nodes: " << randNode << endl;
		cerr << "With these parameters program can not generate connected graph\n";
		getchar();
		exit(0);
	}

	vector<Recovery> recovery;
	vector<double> failures;
	failures = createVectors(&recovery);

	Node *n = new Node[randNode];
	for(int i=0; i<randNode; i++)
		n[i].initialize(i, randNode);

	list<Pair> p = RandomizedNetwork(randNode);
	bool b = isConnected(p, randNode);
	while( b == false ){
		p = RandomizedNetwork(randNode);
		b = isConnected(p, randNode);
	}

	n->connectNeighbours(n, p);
	n->displayNodes(n, randNode);
	int routeNode;
	cout << "\n\n Please select route node number in all nodes ";
	cin >> routeNode;
	while(routeNode<0 || routeNode>=randNode){
		cout << "\n\n Please select *valid* route node number in all nodes ";
		cin >> routeNode;
	}

	Packet pac;
	pac.packetBroading(n, randNode+1-((NUMBEROFLINKS-randNode)/2) , randNode);
	n[routeNode].displayRouting();

	double fail, recover;
	vector<Triple> randomFail;
	Link previousLink;
	Triple randTriple;
	int failCount = 0, recoverCount = 0, broadCastTime;
	int totalTime = 0;
	bool print = false;
	for(int timeCount=0; timeCount<MAXHOURS*60*6; timeCount++){		//40 hours = 40*60*6 times 10-seconds
		broadCastTime = pac.packetBroading(n, randNode+1-((NUMBEROFLINKS-randNode)/2) , randNode);		//for each 10sec.
		timeCount = timeCount + broadCastTime/10000;	//broadcasting of all packages can exceed 10sec for later usages
		if(totalTime <= timeCount - WAITFORPRINT && print){
			print = false;
			cout << "\n*****After link failure or recovery*****\n";
			n[routeNode].displayRouting();
			cout << "For continuing please press the enter\n";
			getchar();
		}

		fail = failures[failCount];
		recover = recovery[recoverCount].timeToRecover;
		if(fail*60*6 <= timeCount){		//Failure operations
			if(fail < recover){		//Failure should come before of recover
				print = true;
				totalTime = timeCount;
				failCount++;	//changing order to next failure in the failure vector
				randTriple = n->createRandomLinks(n, randNode);
				randomFail.insert(randomFail.end(), randTriple);
				int hour = timeCount/360;
				int minute = (timeCount/6)%60;
				cout << "\n-----Failure link is between " << randTriple.num1 << " and " << randTriple.num2 << " at time ";
				cout << hour << " hour " << minute << " minute " << (timeCount%6)*10 << " seconds-----\n";
				for(int cl=0; cl<randNode; cl++)
					n[cl].clearRouting(randNode);
			}
		}
		if(recover*60*6 < timeCount){		//Recovery operations
			if(recover < fail){		//Recover should come before of failure
				print = true;
				totalTime = timeCount;
				randTriple = randomFail[recovery[recoverCount].numberOfFailure];
				recoverCount++;	//changing order to next recovery in the recovery vector
				previousLink.cost = randTriple.cost;
				previousLink.numberToLink = randTriple.num2;
				n[randTriple.num1].connectedNodes.push_back(previousLink);
				previousLink.numberToLink = randTriple.num1;
				n[randTriple.num2].connectedNodes.push_back(previousLink);
				int hour = timeCount/360;
				int minute = (timeCount/6)%60;
				cout << "\n+++++Recovery link is between " << randTriple.num1 << " and " << randTriple.num2 << " at time ";
				cout << hour << " hour " << minute << " minute " << (timeCount%6)*10 << " seconds+++++\n";
				for(int cl=0; cl<randNode; cl++)
					n[cl].clearRouting(randNode);
			}
		}
	}

	cout << "\n\n***Mean value of failures:" << failures[failCount-1]/failCount << endl;
	cout << "\n\n***Mean value of recoveries:" << (recovery[recoverCount-1].timeToRecover - failures[0])/recoverCount << endl << endl;

	return 0;
}

