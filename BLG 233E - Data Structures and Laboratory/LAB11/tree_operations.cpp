#include <iostream>
//#include <stdlib.h>
#include <string.h> 
#include "tree.h"
#include <iomanip>

using namespace std;

void Tree::create() {
	root = NULL;
	nodecount = 0;
}

void Tree::close() {
	emptytree(root);
}

void Tree::emptytree(Phone_node *p) {
	if (p) {
		if (p->left != NULL) {
			emptytree(p->left);
			p->left = NULL;
		}
		if (p->right != NULL) {
			emptytree(p->right);
			p->right = NULL;
		}
		delete p;
	}
}

int Tree::search(char *search_name) {
	Phone_node *traverse;
	traverse = root;
	int countfound = 0;
	bool all = false;
	if (search_name[0] == '*')
		all = true;
	if (all) {
		traverse_inorder(root);
		countfound++;
	}
	else { // single record search
		while (traverse && !countfound) {
			int comparison =
			strcmp(search_name,traverse->name);
			if (comparison < 0)
				traverse = traverse->left;
			else if (comparison > 0)
				traverse = traverse->right;
			else { // if names are equal, record found
				cout << traverse->name <<  endl;
				Phone_number *other = traverse->number_head;
				while(other){
					cout << other->phonenum << "  ";
					other = other->next;
				}
				cout << endl;
				countfound++;
			}
		}
	}
	return countfound;
}

void Tree::traverse_inorder(Phone_node *p) {
	if (p){
		traverse_inorder(p->left);
		cout << p->name << endl;
		Phone_number *traverse = p->number_head;
		while(traverse){
			cout << traverse->phonenum << "  ";
			traverse = traverse->next;
		}
		cout << endl;
		traverse_inorder(p->right);
	}
}

void Tree::add(Phone_node *newnode ) {
	Phone_node *traverse;
	traverse = root;
	int comparison;
	bool added = false;
	if (root == NULL){ //first node being added
		root = newnode;
		nodecount++;
		return;
	}
	while ((traverse != NULL) && (!added)){
		comparison = strcmp(newnode->name,
		traverse->name);
		if (comparison < 0) {
			if (traverse->left != NULL)
				traverse = traverse->left;
			else {
				traverse->left = newnode;
				added = true;
			}
		}
		else if (comparison > 0) {
			if (traverse->right != NULL)
				traverse = traverse->right;
			else {
				traverse->right = newnode;
				added = true;
			}
		}
		else
			cout << "Data cannot repeat.\n";
	}
	if (added) 
		nodecount++;
	cout << "Record added" << endl;
}

void Tree::remove(char *remove_name){
	Phone_node *traverse, *parent;
	traverse = root;
	bool found = false;
	char direction = 'k';
	while (traverse && !found) {
		int comparison = strcmp(remove_name, traverse->name);
		if (comparison < 0) {
			parent = traverse;
			direction = 'l';
			traverse = traverse->left;
		}
		else if (comparison > 0) {
			parent = traverse;
			direction = 'r';
			traverse = traverse->right;
		}
		else // found record to remove
			found = true;
	}
	if (found) {
		if (traverse->left == NULL && traverse->right == NULL) {
			switch (direction) {
				case 'l':
					parent->left = NULL;
					break;
				case 'r':
					parent->right = NULL;
					break;
				default:
					root = NULL;
					break;
			}
		}
		else if (traverse->right == NULL) {
			switch (direction) {
				case 'l':
					parent->left = traverse->left;
					break;
				case 'r':
					parent->right = traverse->left;
					break;
				default:
					root = traverse->left;
					break;
			}
		}
		else if (traverse->left == NULL) {
			switch (direction) {
				case 'l':
					parent->left = traverse->right;
					break;
				case 'r':
					parent->right = traverse->right;
					break;
				default:
					root = traverse->right;
					break;
			}
		}
		else {
			Phone_node *q = traverse->right;
			while ( q->left )
				q = q->left;
			q->left = traverse->left;
			switch (direction) {
				case 'l':
					parent->left = traverse->right;
					break;
				case 'r':
					parent->right = traverse->right;
					break;
				default:
					root = traverse->right;
					break;
			}
		}
	delete traverse;
	}
	else
		cout << "Could not find record to remove.\n";
}

void Tree::update() {
	char name[NAME_LENGTH];
	char choice;
	cout << "Please enter the name of the person you want to update:" << endl;
	cin.ignore(1000, '\n');
	cin.getline(name,NAME_LENGTH);

	Phone_node *traverse;
	traverse = root;
	int countfound = 0;
	bool all = false;
	if (name[0] == '*')
		all = true;
	if (all) {
		traverse_inorder(root);
		countfound++;
	}
	else { // single record search
		while (traverse && !countfound) {
			int comparison =
			strcmp(name,traverse->name);
			if (comparison < 0)
				traverse = traverse->left;
			else if (comparison > 0)
				traverse = traverse->right;
			else { // if names are equal, record found
				cout << traverse->name <<  endl;
				Phone_number *other = traverse->number_head;
				while(other){
					cout << other->phonenum << "  ";
					other = other->next;
				}
				cout << endl;
				countfound++;
			}
		}
	}

	int personcount = countfound;

	if (personcount == 0)
		cout << "Could not find record matching criteria" << endl;
	else {
		cout << "Record found." << endl;
		cout << "Do you want to update? (y/n) ";
		do {
			cin >> choice;
		} while (choice != 'y' && choice != 'n');
		if (choice == 'n') 
			return;

		Phone_number *numaralar = traverse->number_head;
		remove(traverse->name);


		Phone_node *newnode = new Phone_node;
		newnode->number_head = new Phone_number;
		cout << "Please enter new name" << endl;
		cin.ignore(1000, '\n');
		cin.getline(newnode->name, NAME_LENGTH);

		newnode->number_head = numaralar;
		newnode->left = NULL;
		newnode->right = NULL;
		add(newnode);

		cout << "Record successfully updated" << endl;
	}
	getchar();
}