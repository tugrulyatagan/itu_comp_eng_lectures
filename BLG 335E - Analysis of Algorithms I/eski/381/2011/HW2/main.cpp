
#include <time.h>
#include "Data.h"

#define LOOP 1

using namespace std;

int main() {
	Line L,A[1001];
	clock_t t1, t2,t3,t4;
	string inputName;
	int size, loopTime;
	string outputName[4];
	for(int i=1; i<=3; i++){
		// We have 3 .txt files for sorting. Therefore i counts for 1 to 3.
		if(i==1){
			//First iteration, files' names chosen as following.
			inputName = "data1.txt";
			outputName[0] = "insertionsort1.txt";	outputName[1] = "quicksort1.txt";	outputName[2] = "radixsort1.txt";	outputName[3] = "heapsort1.txt";
		}
		if(i==2){
			//Second iteration, files' names chosen as following.
			inputName = "data2.txt";
			outputName[0] = "insertionsort2.txt";	outputName[1] = "quicksort2.txt";	outputName[2] = "radixsort2.txt";	outputName[3] = "heapsort2.txt";
		}
		if(i==3){
			//Third iteration, files' names chosen as following.
			inputName = "data3.txt";
			outputName[0] = "insertionsort3.txt";	outputName[1] = "quicksort3.txt";	outputName[2] = "radixsort3.txt";	outputName[3] = "heapsort3.txt";
		}
		
		t1 = clock();
		for(loopTime = 0; loopTime<LOOP; loopTime++){	
			size = L.read(A, inputName) -1;	
			L.insertionSort(A,size);	//Call insertion sort for LOOP times
		}
		t2 = clock();
		cout<<endl<<"\nClock time for insertion sort with " <<inputName <<" : "<< t2-t1 <<"ms";
		L.write(A, outputName[0]);	//Writing array to output file
	

		t1 = clock();
		for(loopTime = 0; loopTime<LOOP; loopTime++){ 
			size = L.read(A, inputName) -1;
			L.quickSort(A,1,size);		//Call quick sort for LOOP times
		}
		t2 = clock();
		cout<<endl<<"Clock time for quick sort with " <<inputName <<" : " << t2-t1 <<"ms";
		L.write(A, outputName[1]);	//Writing array to output file


		t1 = clock();
		for(loopTime = 0; loopTime<LOOP; loopTime++){ 
			size = L.read(A, inputName) -1;
			L.radixSort(A, 4);		//Call radix sort for LOOP times
		}
		t2 = clock();
		cout<<endl<<"Clock time for radix sort with "<< inputName <<" : " << t2-t1 <<"ms";
		L.write(A, outputName[2]);	//Writing array to output file


		t1 = clock();
		for(loopTime = 0; loopTime<LOOP; loopTime++){ 
			size = L.read(A, inputName) -1;		
			L.heapSort(A);	//Call heap sort for LOOP times
		}
		t2 = clock();
		cout<<endl<<"Clock time for heap sort with " <<inputName <<" : "<< t2-t1 <<"ms";
		L.write(A, outputName[3]);	//Writing array to output file
	
	}
	getch(); 

	return 0;}








