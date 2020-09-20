/********************************************************************
*	Name Surname		: Abdullah AYDEÐER							*
*   Number				: 040090533									*
*	University			: Istanbul Technical University				*
*	Lecture				: Computer Communications					*
*	Lecturer			: Sema OKTUG								*
*	Project Number		: 2											*
*	Created Date		: 26.12.2012								*
*	Purpose of class	: Keeping newtork packets' info for routing	*
*********************************************************************/
#ifndef PACKET_H
#define PACKET_H	//define packet header once

#include "Node.h"

class Packet{
	public:
		Packet(){};
		int ownerId;		//owner node of packet
		int parentId;		//previous node of package(just before now)
		int currentNode;		//current node of package
		vector<Link> packetData;	//packet-data will be created at first step according to neighbours of all nodes
		vector<Link> nodesToSent;	//this will change for every hop
		int age;		//age of packet- if it is less than zero, it will die
		int timeOfPath;	
		vector<Packet> createAllPackets(Node *, int, int);	//creates packetData
		int packetBroading(Node *, int, int);	//Broadcasting packets to all others
		void addPacketToAll(vector<Packet> *);	//adding new packet to aggregation of packets
		bool isAdded(vector<Packet> );
};

#endif

