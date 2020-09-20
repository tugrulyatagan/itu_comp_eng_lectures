#ifndef TREE_H
#define TREE_H
#include "node.h"

struct tree{
	node *root;
	node *insertTree(node *nptr,int,int);
	void printPreorder(node *);
	void printInorder(node *);
	void printPostorder(node *);
	int findMax(node *);
	int findMin(node *);
	int findNumNode(node *);
	int findNumLeaf(node *);
	int calculateDepth(node *);
	int calculateSum(node *);
	float calculateAverage(node *);
	void removeTree(node *);
};

#endif
