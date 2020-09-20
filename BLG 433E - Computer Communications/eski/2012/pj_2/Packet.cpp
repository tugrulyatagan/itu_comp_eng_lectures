#include "Packet.h"

vector<Packet> Packet::createAllPackets(Node *n, int age, int numOfNode){
	vector<Packet> vPack;
	Link l;
	list<Link>::iterator it;
	for(int i=0; i<numOfNode; i++){	//for all nodes in network
		Packet p;
		p.age = age;
		p.timeOfPath = 0;	//for creating, initialize cost as '0'
		for(it = n[i].connectedNodes.begin(); it != n[i].connectedNodes.end(); it++){	//for all neighbours
			l = (*it);	
			p.packetData.push_back(l);	//learn about it
		}
		p.nodesToSent = p.packetData;	//firstly nodesToSent will equal to packetData since node will sent packet to nodes which are already in packet
		p.ownerId = i;	//owner of packet initialized
		p.currentNode = i;	
		p.parentId = -1;	//it does not have any parent
		vPack.push_back(p);
	}
	return vPack;	//return back to all packages which are created for nodes
}

int Packet::packetBroading(Node *n, int age, int numOfNode){
	Link l;
	Packet p;
	Pair pair, pair2;
	list<Link>::iterator it;
	Packet oldPacket;
	int order, broadCastTime = 0;

	for(int cl=0; cl<numOfNode; cl++)
		n[cl].clearIsAdded(numOfNode);

	vector<Packet> allPacketsToSent = createAllPackets(n, age, numOfNode);
		
	while(!allPacketsToSent.empty()){		//wait for all packets to die
		oldPacket = allPacketsToSent[0];
		p.ownerId = oldPacket.ownerId;
		p.parentId = oldPacket.currentNode;	 
		p.age = oldPacket.age -1;
		allPacketsToSent.erase(allPacketsToSent.begin());
		if(oldPacket.age > 0){	//if it is not invalid(not died)
			for(int i = 0; i < oldPacket.nodesToSent.size(); i++){		//Sent packet to all neighbours
				order = oldPacket.nodesToSent[i].numberToLink;
				pair.num1 = oldPacket.ownerId;
				pair.num2 = oldPacket.nodesToSent[i].cost + oldPacket.timeOfPath;
				pair2 = n[order].routingTable[oldPacket.ownerId];					
				p.currentNode = order;
				if(oldPacket.ownerId == oldPacket.currentNode){	//for first packages
					if(pair2.num2 > pair.num2){
						n[order].routingTable[oldPacket.ownerId] = pair;	//update routing-table
					}
				}
				else if(pair2.num2 > pair.num2 && oldPacket.ownerId != order){
					pair.num1 = oldPacket.currentNode;
					n[order].routingTable[oldPacket.ownerId] = pair;
				}
				//new packages will be created at this below if
				if(n[p.ownerId].isAdded[p.currentNode] == -1){  
					p.packetData = oldPacket.packetData;
					p.timeOfPath = oldPacket.timeOfPath;  
					p.timeOfPath += oldPacket.nodesToSent[i].cost;
					for(it = n[order].connectedNodes.begin(); it != n[order].connectedNodes.end(); it++){
						l = (*it);
						p.nodesToSent.push_back(l);
					}
					p.addPacketToAll(&allPacketsToSent);
					n[p.ownerId].isAdded[p.currentNode] = 1;
					p.nodesToSent.clear();
				}
			}
		}
		else{
			int a=0;
			a--;
		}
		if(allPacketsToSent.size() == 0)
			broadCastTime = oldPacket.timeOfPath;
	}
	for(int m=0; m<numOfNode; m++){
		n[m].routingTable[m].num1 = m;
		n[m].routingTable[m].num2 = 0;
	}
	return broadCastTime;
}

bool Packet::isAdded(vector<Packet> allPacks){
	bool f1 = false, f2 = false;
	for(int i=0; i<allPacks.size(); i++){
		if(currentNode == allPacks[i].currentNode && ownerId == allPacks[i].ownerId)
			return true;
	}
	return false;
}

void Packet::addPacketToAll(vector<Packet> *allPacketsToSent){
	int i;
	for(i=0; i<allPacketsToSent->size(); i++){
		if(timeOfPath < (*allPacketsToSent)[i].timeOfPath)
			break;
	}
	allPacketsToSent->insert(allPacketsToSent->begin()+i, *this);
}
