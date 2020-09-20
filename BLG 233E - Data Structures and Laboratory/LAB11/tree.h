#include "node.h"

struct Tree {
	Phone_node *root;
	int nodecount;
	void create();
	void close();
	void emptytree(Phone_node *);
	void add(Phone_node *newnode );
	void remove(char *);
	void traverse_inorder(Phone_node *);
	int search(char *);
	void Tree::update();
};

