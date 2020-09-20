/********************************************************************************
*	Name Surname: Aykut Akin													*
*	Number		: 040080177														*
*	Due Date	: 23.03.2011													*
*																				*
*	Every information about functions and classes can be found in report		*
*																				*
*********************************************************************************/

#ifndef __HEAP_H__
#define __HEAP_H__

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <fstream>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>

#define SIZE 100

using namespace std;

class Heap{

	int heapSize;
	int prefList[SIZE+1][SIZE+1];
	void readData(string fileName);
	void readwData(string wfileName,string num);

public:
	
	int engagements[SIZE+1];
	int *count;
	int **roots;
	int **inverse;
	int *wealth;

	Heap(string optimal,string fileName, string wfileName="", string wNum="");
	~Heap();

	int getHeapSize();
	void writeData(string fileName, int time);
};

#endif