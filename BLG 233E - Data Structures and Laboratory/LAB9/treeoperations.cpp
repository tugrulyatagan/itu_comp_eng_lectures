#include <iostream>
#include "tree.h"
using namespace std;

node *tree::insertTree(node *nptr,int ele,int count){
	if(nptr == NULL){
		nptr = new node;
		nptr->right = NULL;
		nptr->left = NULL;
		nptr->number = ele;
		if(root == NULL)
			root = nptr;
	}
	else{
		if(count % 2 == 0)
			nptr->left = insertTree(nptr->left,ele,count);
		else
			nptr->right = insertTree(nptr->right,ele,count);
	}
	return nptr;
}

void tree::printPreorder(node *nptr){
	if(nptr){
		cout << nptr->number << "  ";
		printPreorder(nptr->left);
		printPreorder(nptr->right);
	}
}

void tree::printInorder(node *nptr){
	if(nptr){
		printInorder(nptr->left);
		cout << nptr->number << "  ";
		printInorder(nptr->right);
	}
}

void tree::printPostorder(node *nptr){
	if(nptr){
		printPostorder(nptr->left);
		printPostorder(nptr->right);
		cout << nptr->number << "  ";
	}
}

int tree::findMax(node *nptr){
	if(nptr == NULL)
		return -1;
	int leftmax = findMax(nptr->left);
	int rightmax = findMax(nptr->right);
	if((nptr->number > leftmax) && (nptr->number > rightmax))
		return nptr->number;
	return max(leftmax,rightmax);
}

int tree::findMin(node *nptr){
	if(nptr == NULL)
		return findMax(root);
	int leftMin = findMin(nptr->left);
	int rightMin = findMin(nptr->right);
	if((nptr->number < leftMin) && (nptr->number < rightMin))
		return nptr->number;
	return min(leftMin,rightMin);
}

int tree::findNumNode(node *nptr){
	if(nptr == NULL)
		return 0;
	return findNumNode(nptr->left) + findNumNode(nptr->right) + 1;
}

int tree::findNumLeaf(node *nptr){
	if(nptr == NULL)
		return 0;
	if(nptr->left == NULL && nptr->right == NULL)
		return 1;
	return findNumLeaf(nptr->left) + findNumLeaf(nptr->right);
}

int tree::calculateDepth(node *nptr){
	if(nptr == NULL) 
		return 0;
	int leftDepth = calculateDepth(nptr->left);
	int rightDepth = calculateDepth(nptr->right);
	return max(leftDepth + 1, rightDepth + 1);
}

int tree::calculateSum(node *nptr){
	if(nptr == NULL)
		return 0;
	return nptr->number + calculateSum(nptr->left) + calculateSum(nptr->right);
}

float tree::calculateAverage(node *nptr){
	return float(calculateSum(nptr)) / float(findNumNode(nptr));
}

void tree::removeTree(node *nptr){
	if(nptr->left != NULL)
		removeTree(nptr->left);
	if(nptr->right != NULL)
		removeTree(nptr->right);
	delete nptr;
}