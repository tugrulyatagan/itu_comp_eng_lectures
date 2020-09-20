
/************************************************************************************************
* About the writer;																				*
* Student Name: Abdullah AYDEGER																*
* Student Number: 040090533																		*
*************************************************************************************************
* About the code;																				*
* File Name: BTree.h																			*
* Reason Of Writing: Hiring all necessary variables and also their pointers in the B-Tree		*
*						 is supplied by this class.												*
*************************************************************************************************/

#ifndef _BTREE_H_
#define _BTREE_H_

#include <cstdlib>
#include <fstream>
#include <direct.h>
#include "Node.h"
#define writeFileName "output.txt"	//output file name

class BTree{
	public:
		Node* root;
		int m;
		BTree(int );

		int read(string);
		string readWord(string, int, int);

		void B_TREE_INSERT(string, string);
		void B_TREE_INSERT_NONFULL(Node *, string, string);
		void B_TREE_SPLIT_CHILD(Node *, int );
		NodeData B_TREE_SEARCH(Node *, string k);

};
		

#endif