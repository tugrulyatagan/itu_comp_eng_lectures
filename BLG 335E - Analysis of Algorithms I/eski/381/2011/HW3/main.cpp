#include <conio.h>
#include <time.h>
#include "BTree.h"

#define numOfSearching 29		//Number of randomized search
#define fileName "sonnets.txt"	//Inout file name

int main() {
	int order, i, j;
	clock_t t1, t2;

	srand(time(NULL));

	cout<<"Please enter the order value of B-Tree:";
	cin >> order;	
	BTree *BT = new BTree(order);
	
	int sentence = BT->read(fileName);
	
	double totalTime = 0;

	for(int loop=0; loop<numOfSearching; loop++){
		i = rand()%8 +1;
		j = rand()%(sentence-1) +1;

		t1 = clock();
		NodeData nd = BT->B_TREE_SEARCH(BT->root, BT->readWord(fileName, j, i));
		t2 = clock();

		totalTime = totalTime + (t2-t1)/(double)CLOCKS_PER_SEC;

		if(nd.data.empty())
			cout<< endl << endl << "There are no word in the ("<< j << "," << i << ") place in the sonnet ";				
		else{
			cout<< endl << endl << nd.data << " is placed in: " ;
			for(int i=0; !nd.places[i].empty(); i++)
				cout << nd.places[i] << "  " ;
		}
	}

	cout<< endl << endl << "Total time of searching: " << totalTime << " second";
	getch(); 

	return 0;
}










