#include <iostream>
#include <ctime>
#include "tree.h"
#include "stack.h"
#include "queue.h"
using namespace std;

Leaf *tree::createTree(){
	int N;
	cout << "Enter size(N) : ";
	cin >> N;
	Leaf* root = new Leaf; // ilk önce root eklenir
	root->left = NULL;
	root->right = NULL;
	root->number = 1;//1 + rand() % N; 
	for(int i = 2; i <= N; i++){	
		int order = i;
		bool *bin = new bool[N];
		int digit=0;
		int depth = log(static_cast<float>(order))/log(static_cast<float>(2)); // log2 tabanýnda N derinlik

		while(order != 0){
			if(order % 2 == 0) // 2 ye tam bölünme sayisi binary 0 larin sayisi
				bin[digit++] = 0;
			else if (order % 2 == 1)
				bin[digit++] = 1;
			order = order / 2; // 2 ye bole bole dongu doner
		}	

		Leaf* nptr = new Leaf;
		nptr->left = NULL;
		nptr->right = NULL;
		nptr->number = i;//1 + rand() % N;
		Leaf * curr = root;

		for(int i = 0; i < depth - 1; i++){ // burada eklenecek yerin bir ustune(parent) gelinir
			if(bin[i] == 0) // 0 ise sola gec
				curr = curr->left;
			else if(bin[i] == 1) // 1 ise saga gec
				curr = curr->right;
		}
		if(curr->left == NULL) // sol cocuk bossa sola ekle
			curr->left = nptr; 
		else // sol bos degilse saga ekle 
			curr->right = nptr;
	}	
	return root;
}

void tree::printPreorder(Leaf *nptr){
	if(nptr){
		cout << nptr->number << "  ";
		printPreorder(nptr->left);
		printPreorder(nptr->right);
	}
}

void tree::printInorder(Leaf *nptr){
	if(nptr){
		printInorder(nptr->left);
		cout << nptr->number << "  ";
		printInorder(nptr->right);
	}
}

void tree::printPostorder(Leaf *nptr){
	if(nptr){
		printPostorder(nptr->left);
		printPostorder(nptr->right);
		cout << nptr->number << "  ";
	}
}

void tree::searchInorder(Leaf * traverse, int value){
	if(traverse){
		searchInorder(traverse->left, value);
		cout << traverse->number << "   ";
		if(value == traverse->number)
			return;
		searchInorder(traverse->right, value);
	}
}

void tree::searchBFS(int value){
	Queue Q;
	Q.create();
	Q.enqueue(root);
	while(!Q.isempty()){
		Leaf *temp;
		temp = Q.dequeue();
		if(temp->left != NULL)
			Q.enqueue(temp->left);
		if(temp->right != NULL)
			Q.enqueue(temp->right);
		cout << temp->number << "   ";
		if(temp->number == value)
			break;
	}
}

void tree::searchDFS(int value){
	Stack S;
	S.create();
	S.push(root);
	while(!S.isempty()){
		Leaf *temp;
		temp = S.pop();
		if(temp->left != NULL)
			S.push(temp->left);
		if(temp->right != NULL)
			S.push(temp->right);
		cout << temp->number << "   ";
		if(temp->number == value)
			break;
	}
}

void tree::removeTree(Leaf *nptr){
	if(nptr->left != NULL)
		removeTree(nptr->left);
	if(nptr->right != NULL)
		removeTree(nptr->right);
	delete nptr;
}
