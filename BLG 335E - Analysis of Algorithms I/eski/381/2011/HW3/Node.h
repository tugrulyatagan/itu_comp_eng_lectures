
/************************************************************************************************
* About the writer;																				*
* Student Name: Abdullah AYDEGER																*
* Student Number: 040090533																		*
*************************************************************************************************
* About the code;																				*
* File Name: Node.h																				*
* Reason Of Writing: Holding each key in the Node class, therefore operations on Node can 		*
*						 be done very easily and with object oriented approach						*
*************************************************************************************************/

#ifndef _NODE_H_
#define _NODE_H_

#include "NodeData.h"

class Node{
	public:
		int t;				//t value for determining max. and min. datas holded by Nodes
		bool leaf;			//is it leaf or not
		Node **c;			//pointer of Nodes' children
		NodeData *nd;		//holding necessary datas in the nodes 
		int n;				//number of keys currently stored in node x

		Node(){};

		Node(int num){				//This is constructor with integer parameter.
			t = num;				// According to this parameter, allocating necessary places from memory.
			nd = new NodeData[2*t];
			c = new Node*[2*t+1];
		}

		
};

#endif

