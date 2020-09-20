/**********************************************
*** Student Name: Abdullah AYDEGER			***	
*** Student Number : 040090533				***
*** Lecture : Advanced Data Structures		***
*** Lecturer : Zehra CATALTEPE				***
**********************************************/

/* All functions are written by me. Therefore no reference from here. */

#include "Data.h"

using namespace std;

void Line::insertionSort(Line dizi[1001], int length){
	/* This function takes one array of structures, which have variables integer and string.
	   Function sorts the structure according to integer values following the sample insertionsort algorithm */
	int i,key1;
	string key2;
	for(int j=2; j<=length; j++){
		key1 = dizi[j].veri1;
		key2 = dizi[j].veri2;
		i = j-1;
		while(i>0 && dizi[i].veri1<key1){
			dizi[i+1].veri1 = dizi[i].veri1;
			dizi[i+1].veri2 = dizi[i].veri2;
			i -=1;
		}
		dizi[i+1].veri1 = key1;
		dizi[i+1].veri2 = key2;
	}
}

void Line::quickSort(Line dizi[1000], int p, int r){
	/* This function takes one array of structures, which have variables integer and string, and two integer as parameters. 
	   Function sorts the structure according to integer values following the sample quicksort algorithm */
	if(p<r){
		int q = partition(dizi, p, r);
		quickSort(dizi, p, q-1);
		quickSort(dizi, q+1, r);
	}
}

int Line::partition(Line dizi[1000], int p, int r){
	/* This function split the array of structure by 2 parts. */
	int key1;
	string key2;
	int x = dizi[r].veri1;
	int i = p-1;
	for(int j=p; j<=r-1; j++){
		if(dizi[j].veri1>= x){
			i +=1;
			exchange(dizi, i, j);
		}
	}
	exchange(dizi, i+1, r);	
	return i+1;
}

void Line::exchange(Line dizi[1000], int i, int j){
	/* This function is written for exchanging two elements of array of structures 
	   according to given parameters */
	int key1 = dizi[i].veri1;
	string	key2 = dizi[i].veri2;
	dizi[i].veri1 = dizi[j].veri1;
	dizi[i].veri2 = dizi[j].veri2;
	dizi[j].veri1 = key1;
	dizi[j].veri2 = key2;
}

void Line::countingSort(Line dizi[1001], Line sorted[1001], int ordered[1000], int k){
	/* This function sorts the given array with integer parameters. This given integer array
	    must be take values from 0 to k(parameter for this function).
		This sorted integer array is hiding in array is named sorted with type of structure of Line
		Finally, this sorted array is placed in dizi(main array)*/
	int a[11] = {0};		//One temperature integer array
	for (int i=1;i<=1000;i++){
		a[ordered[i]]++;
	}
	for (int i=1;i<10;i++){    
		a[i] += a[i-1];
	}    

	for (int i=1000;i>=1;i--){
		sorted[a[ordered[i]]].veri1 = dizi[i].veri1;	//Main array(dizi) is sorting in sorted array.
		sorted[a[ordered[i]]].veri2 = dizi[i].veri2;
		a[ordered[i]]--;                                                                                                                                                
	}	
	for(int j=1; j<= 1000; j++){
		dizi[j].veri1 = sorted[j].veri1;	//Sorted array is inserting main array back.
		dizi[j].veri2 = sorted[j].veri2;
	}
}

void Line::radixSort(Line dizi[1000], int d){
	/* This function sorts the array of Line structure with respect to their integer values.
	    Function takes one integer which is number of digits for determining loop. */
	int newdizi[1001];	//This is used for sending parameter countingsort
	Line sort[1001];
	for(int i=1; i<=d; i++){
		if(i == 1)
			for(int j=1; j<=1000; j++){
				newdizi[j] = dizi[j].veri1 %10;		//newdizi = last(less meaning) digit of dizi[j].veri1
			}
		if(i == 2)
			for(int j=1; j<=1000; j++){
				if(dizi[j].veri1 >=10)
					newdizi[j] = (dizi[j].veri1%100 - dizi[j].veri1 %10)/10;	//newdizi = third digit of dizi[j].veri1
				else
					newdizi[j] = 0;
			}
		if(i == 3)
			for(int j=1; j<=1000; j++){
				if(dizi[j].veri1 >= 100)
					newdizi[j] = (dizi[j].veri1 - dizi[j].veri1 %100)/100; //newdizi = second digit of dizi[j].veri1
				else
					newdizi[j] = 0;
			}
		if(i == 4)
			for(int j=1; j<=1000; j++){
				if(dizi[j].veri1 >=1000)
					newdizi[j] = dizi[j].veri1/1000;	//newdizi = first(most significant) digit of dizi[j].veri1
				else
					newdizi[j] = 0;
			}
		countingSort(dizi, sort, newdizi, 10);	//Calling counting sort with given parameters
	}
	for(int j=1; j<= 500; j++){
		exchange(dizi,j, 1001-j);	//Make array reverse order
	}
}

void Line::heapSort(Line dizi[1000]){
	/* This is standard function for heap sort. */
	buildMinHeap(dizi, heapSize);	//Firstly, build the heap
	for(int i=heapSize; i>=2; i--){	
		exchange(dizi,1,i);	
		heapSize--;	
		minHeapify(dizi, 1);
	}
}

void Line::buildMinHeap(Line dizi[1000], int size){
	/* This function calls minHeapify for build Min Heap from given parameters */
	int tempSize = heapSize;
	for(int i=heapSize/2; i>=1; i--)
		minHeapify(dizi, i);
}

void Line::minHeapify(Line dizi[1000], int i){
	/* This is recursive function for determining Min Heap */
	int largest;
	int l = 2*i;		//Left of i'th node equals to 2*i
	int r = 2*i +1;		//Right of i'th node equals to 2*i+1
	if(l <= heapSize && dizi[l].veri1 < dizi[i].veri1)
		largest = l;
	else
		largest = i ;
	if(r <= heapSize && dizi[r].veri1 < dizi[largest].veri1) 
		largest = r;
	if(largest !=i){
		exchange(dizi, i, largest);
		minHeapify(dizi, largest);
	}
}

int Line::read(Line dizi[1001],string inputName){
	/* This function open input file with given inputName parameter,
	   and assign each item to structure array. */
	ifstream read;
	int x=0;
	read.open(inputName,ios::in);
		if (read.fail()) {	
		  cerr << "Could not open file ";
		  cerr << inputName;
		  cerr << ".\n";
		  return 1;
		  }
		while(!read.eof()){
			x++;
			read >> dizi[x].veri1 >> dizi[x].veri2;
		} 
	heapSize = x-1;	//This variable is required for heapSort
	read.close();
	return x;
}

void Line::write(Line dizi[1001], string outputName){
	/* This function write an array of structure to output with given outputName */
	ofstream write;
	write.open(outputName);
		for(int i=1; i<=1000; i++)
			write << dizi[i].veri1 <<" "<< dizi[i].veri2 <<endl;
	write.close();
};