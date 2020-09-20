#include <iostream>
#include <ctime>
#include <cstdlib>
#include "tree.h"
using namespace std;

void createTree();

tree T;

int main(){
	cout << "Tree Program" << endl;
	srand ( time(NULL) );

	createTree();
	cout << "Tree craeted." << endl;

	cout << "Preorder: ";
	T.printPreorder(T.root);
	cout << endl;

	cout << "Inorder: ";
	T.printInorder(T.root);
	cout << endl;

	cout << "Postrder: ";
	T.printPostorder(T.root);
	cout << endl;

	cout << "Max: ";
	cout << T.findMax(T.root);
	cout << endl;

	cout << "Min: ";
	cout << T.findMin(T.root);
	cout << endl;

	cout << "Node number: ";
	cout << T.findNumNode(T.root);
	cout << endl;

	cout << "Leaf number: ";
	cout << T.findNumLeaf(T.root) + 1;
	cout << endl;

	cout << "Depth: ";
	cout << T.calculateDepth(T.root);
	cout << endl;

	cout << "Sum: ";
	cout << T.calculateSum(T.root);
	cout << endl;

	cout << "Avarage: ";
	cout << T.calculateAverage(T.root);
	cout << endl;

	T.removeTree(T.root);
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
		T.insertTree(T.root ,A[i],i);
	}
	delete[] A;
}
