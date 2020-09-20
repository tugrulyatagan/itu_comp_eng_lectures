#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "stack.h"
using namespace std;

void print();
void makemaze();
bool allvisit();
bool checknegh(cell x)
cell unvisitednegh(cell x);


Stack S;
cell m[MAZESIZE][MAZESIZE];

int main(){
	S.create();
	srand (time(NULL));

	//makemaze();


	print();
	S.close();
	return 0;
}

void makemaze(){
	for(int i = 0; i < MAZESIZE * MAZESIZE;i++){
		m[i / MAZESIZE][i % MAZESIZE].left = 1;
		m[i / MAZESIZE][i % MAZESIZE].right = 1;
		m[i / MAZESIZE][i % MAZESIZE].up = 1;
		m[i / MAZESIZE][i % MAZESIZE].down = 1;
	}
	m[0][0].visited = 1;
	int current = 0;

	while(!allvisit()){
		if(){



		}
		else if(){



		}
		else{



		}//else kapaniyor
	}//while kapaniyor
}

void print(){
	for(int i = 0; i < MAZESIZE; i++){
		for(int j = 0; j < MAZESIZE; j++){
			if(m[i][j].up)
				cout << " -";
			else 
				cout << " ";
		}
		cout << endl;
		cout << "|";
		for(int j = 0; j < MAZESIZE; j++){
			if(m[i][j].right)
				cout << m[i][j].val << "|";
			else
				cout << m[i][j].val << " ";
		}
		cout << endl;
	}
	for(int i = 0; i < MAZESIZE; i++){
		if(m[MAZESIZE-1][i].down)
			cout << " -";
	}
	cout << endl;
}

bool allvisit(){
	for (int i = 0; i < MAZESIZE * MAZESIZE; i++)
		if(m[i / MAZESIZE][i % MAZESIZE].visited == 0)
			return 0;
	return 1;
}

cell unvisitednegh(cell x){


	return m[3][4];
}


/*his
	cell *newcell = new cell;
	newcell->val = 'a';
	S.push(newcell);
	cout << S.pop()->val << endl;


	m[1][5].val = 'b';
	S.push(&m[1][5]);
	cout << S.pop()->val << endl;



	printf ("Random number: %d\n", rand() % 100);
*/