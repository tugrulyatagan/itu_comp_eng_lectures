#ifndef __BTREE_H__
#define __BTREE_H__

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <fstream>
#include <string>
#include <direct.h>
#include "BTNode.h"

using namespace std;

class BTree{

	public:
		BTNode* root;
		string name;
		string filename;

		BTree(string);
		BTree(string, string);

		void BT_Insert(double);
		void BT_Split_Child(BTNode*, int, BTNode*);
		void BT_Insert_Nonfull(BTNode*, double);

		void writeData(BTNode*);
		void writeIntervalData();
		void readData();
};

#endif

		