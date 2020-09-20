#ifndef DATA_H
#define DATA_H
#include <string>
#include <string>
#include <fstream>
#include <conio.h>
#include <iostream>
#include <math.h>
#include <stdlib.h> 
using namespace std;

struct Line{
	int veri1;	
	string veri2;
	int heapSize;
	void insertionSort(Line [], int);
	void quickSort(Line [], int, int);
	int partition(Line [], int , int );
	void exchange(Line [], int, int);
	void radixSort(Line [], int);
	void countingSort(Line [], Line [], int [], int);
	void buildMinHeap(Line [], int);
	void minHeapify(Line [], int);
	void heapSort(Line []);
	int read(Line [], string);
	void write(Line [], string);
};

#endif
