#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <fstream>
#include <string>
#include <direct.h>
#include "BTNode.h"
#include "BTree.h"
#include <time.h>

using namespace std;

double randomnumgen();
BTree* interval;
BTNode *BTIntervalSearch(BTNode* node, double a, double b);

int main(){
	
	string command;
	bool tryagain=true;
	srand ( time(NULL) );

	while(tryagain){//loop until the right command

		cout << endl <<"Command Example for creating B-Tree: btinsert -n 10000 -o BtreeQ1"<<endl;
		cout << "Command Example for Interval Search: btintervalsearch -i BtreeQ1 a b -o out.txt"<<endl<<endl;
		cout << "Please write a command: ";
		getline(cin,command);
	
		if(command.find(" -n ")!=string::npos || command.find(" -i ")!=string::npos && command.find(" -o ")!=string::npos)
			tryagain = false;
	}
	
	if(!command.substr(0,8).compare("btinsert")){
		BTree T(command.substr(21));
		for(int i=0; i<10000; i++)
			T.BT_Insert(randomnumgen());
		T.writeData(T.root);
	}

	if(!command.substr(0,16).compare("btintervalsearch")){
		string subcommand=command.substr(20);
		BTree T(subcommand.substr(0,7));
		T.readData();
		interval = new BTree(subcommand.substr(0,7),subcommand.substr(subcommand.find_last_of(" ")+1));
		double a = atof(subcommand.substr(8,subcommand.substr(8).find_first_of(" ")).c_str());
		int k=subcommand.substr(8).find_first_of(" ");
		int m=subcommand.substr(subcommand.substr(8).find_first_of(" ")).find_first_of(" ");
		double b = atof(subcommand.substr(9+k,8+m).c_str());
		interval->root = BTIntervalSearch(T.root,a,b);
		interval->writeIntervalData();
	}

	return EXIT_SUCCESS;
};

double randomnumgen(){
  return 1000*rand()/(RAND_MAX + 1.0);
}

BTNode *BTIntervalSearch(BTNode* node, double a, double b) {

	if (node == NULL) 
		return interval->root;

	for (int i = 1; i <= node->n; i++) {
		if (node->keys[i] >= b) {
			BTIntervalSearch(node->c[i], a, b);	   
			if (node->keys[i] == b)
				interval->BT_Insert(node->keys[i]);		
			return interval->root;
		} 
		
		else if (node->keys[i] >= a) {
			if (node->keys[i] > a) 
				BTIntervalSearch(node->c[i], a, b);	
			interval->BT_Insert(node->keys[i]);
		}
   }
   BTIntervalSearch(node->c[(node->n)+1], a, b);
};


