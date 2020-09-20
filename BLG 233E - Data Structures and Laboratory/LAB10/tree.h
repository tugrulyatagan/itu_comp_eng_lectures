#ifndef TREE_H
#define TREE_H
#include "Leaf.h"

struct tree{
	Leaf *root;
	Leaf *createTree();
	void printPreorder(Leaf *);
	void printInorder(Leaf *);
	void printPostorder(Leaf *);
	void searchInorder(Leaf *,int);
	void searchBFS(int);
	void searchDFS(int);
	void removeTree(Leaf *);
};

#endif
