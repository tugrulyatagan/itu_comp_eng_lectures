#ifndef __BTNODE_H__
#define __BTNODE_H__

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <fstream>
#include <string>
#include <direct.h>

using namespace std;

class BTNode{

	public:            
		bool leaf;       // is it a leaf node or not?
		int n;           // number of keys currently stored in node x
		double keys[200];     // array of keys
		BTNode *c[201];  // pointers to children
		BTNode();
};

#endif