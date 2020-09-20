#include <iostream>
#include <ctime>
#include <cstdlib>
#include "tree.h"
using namespace std;

void createTree();
node *insertTree(node *nptr,int);
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

tree T;

int main(){
	cout << "Tree Program" << endl;
	srand ( time(NULL) );

	createTree();
	cout << "Tree craeted." << endl;

	cout << "Preorder: ";
	printPreorder(T.root);
	cout << endl;

	cout << "Inorder: ";
	printInorder(T.root);
	cout << endl;

	cout << "Postrder: ";
	printPostorder(T.root);
	cout << endl;

	cout << "Max: ";
	cout << findMax(T.root);
	cout << endl;

	cout << "Min: ";
	cout << findMin(T.root);
	cout << endl;

	cout << "Node number: ";
	cout << findNumNode(T.root);
	cout << endl;

	cout << "Leaf number: ";
	cout << findNumLeaf(T.root);
	cout << endl;

	cout << "Depth: ";
	cout << calculateDepth(T.root);
	cout << endl;

	cout << "Sum: ";
	cout << calculateSum(T.root);
	cout << endl;

	cout << "Avarage: ";
	cout << calculateAverage(T.root);
	cout << endl;

	removeTree(T.root);
	cout << "Tree removed." << endl;

	return 0;
}

void createTree(){
	int N;
	cout << "Enter size : ";
	cin >> N;
	int *A = new int[N];
	T.root = NULL;
	for(int i = 0; i < N; i++ ){
		A[i] = 1 + rand() % N;
		T.root = insertTree(T.root,A[i]);
	}
	delete[] A;
}

node *insertTree(node *nptr,int ele){
	if(nptr == NULL){
		nptr = new node;
		nptr->right = NULL;
		nptr->left = NULL;
		nptr->number = ele;
	}
	else{
		if(rand() % 2 == 0)
			nptr->left = insertTree(nptr->left,ele);
		else
			nptr->right = insertTree(nptr->right,ele);
	}
	return nptr;
}

void printPreorder(node *nptr){
	if(nptr){
		cout << nptr->number << "  ";
		printPreorder(nptr->left);
		printPreorder(nptr->right);
	}
}

void printInorder(node *nptr){
	if(nptr){
		printInorder(nptr->left);
		cout << nptr->number << "  ";
		printInorder(nptr->right);
	}
}

void printPostorder(node *nptr){
	if(nptr){
		printPostorder(nptr->left);
		printPostorder(nptr->right);
		cout << nptr->number << "  ";
	}
}

int findMax(node *nptr){
	if(nptr == NULL)
		return -1;
	int leftmax = findMax(nptr->left);
	int rightmax = findMax(nptr->right);
	if((nptr->number > leftmax) && (nptr->number > rightmax))
		return nptr->number;
	return max(leftmax,rightmax);
}

int findMin(node *nptr){
	if(nptr == NULL)
		return findMax(T.root);
	int leftMin = findMin(nptr->left);
	int rightMin = findMin(nptr->right);
	if((nptr->number < leftMin) && (nptr->number < rightMin))
		return nptr->number;
	return min(leftMin,rightMin);
}

int findNumNode(node *nptr){
	if(nptr == NULL)
		return 0;
	return findNumNode(nptr->left) + findNumNode(nptr->right) + 1;
}

int findNumLeaf(node *nptr){
	if(nptr == NULL)
		return 0;
	if(nptr->left == NULL && nptr->right == NULL)
		return 1;
	return findNumLeaf(nptr->left) + findNumLeaf(nptr->right);
}

int calculateDepth(node *nptr){
	if(nptr == NULL) 
		return 0;
	int leftDepth = calculateDepth(nptr->left);
	int rightDepth = calculateDepth(nptr->right);
	return max(leftDepth + 1, rightDepth + 1);
}

int calculateSum(node *nptr){
	if(nptr == NULL)
		return 0;
	return nptr->number + calculateSum(nptr->left) + calculateSum(nptr->right);
}

float calculateAverage(node *nptr){
	return float(calculateSum(nptr)) / float(findNumNode(nptr));
}

void removeTree(node *nptr){
	if(nptr->left != NULL)
		removeTree(nptr->left);
	if(nptr->right != NULL)
		removeTree(nptr->right);
	delete nptr;
}
