#include <iostream>
#include <ctime>
#include <cstdlib>
#include "tree.h"
using namespace std;

int main(){
	tree T;
	cout << "Tree Program" << endl;
	srand ( time(NULL) );

	T.root = T.createTree();
	cout << "Tree is craeted." << endl;

	cout << "Preorder: ";
	T.printPreorder(T.root);
	cout << endl;

	cout << "Inorder: ";
	T.printInorder(T.root);
	cout << endl;

	cout << "Postorder: ";
	T.printPostorder(T.root);
	cout << endl;


	int num;
	cout << "Enter number for searching : ";
	cin >> num;

	cout << "Inorder Search: ";
	T.searchInorder(T.root, num);
	cout << endl;		

	cout << "Breadth First Search: ";
	T.searchBFS(num);
	cout << endl;

	cout << "Depth First Search: ";
	T.searchDFS( num);
	cout << endl;

	T.removeTree(T.root);
	cout << "Tree is removed." << endl;

	return 0;
}
