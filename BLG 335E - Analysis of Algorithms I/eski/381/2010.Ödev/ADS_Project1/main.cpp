
/* This program sorts an array's values into ascending order and calculate the reading, writing, sorting times.*/

#include <iostream>
#include <iomanip>
#include <ctime>
#include <fstream>
#include <string>
#include <direct.h>
#include <cmath>

#define SIZE 100000 // array size
static int heapSize;
int length=1;
bool is_buildheap = false;

using namespace std;

void readData(string fileName, int *a);
void writeData(string fileName, int *a);
void heapsort(int *a);
void buildMaxHeap(int* a);
void max_heapify(int* a,int i);
void writeTime(string command, int read, int sort, int write);

/* function main begins program execution */

int main() 
{     
	string fileName;
	string command;
	int a[SIZE];
	bool tryagain=true;
    clock_t sort_start_clk, sort_end_clk, read_start_clk, read_end_clk, write_start_clk, write_end_clk; 

	while(tryagain){//loop until the right command

		cout << endl <<"Command Example for sorting the numbers: heapsort -i initdata1.txt -t s"<<endl;
		cout << "Command Example for building a heap: heapsort -i initdata1.txt -t b"<<endl<<endl;

		cout << "Please write a command: ";
		getline(cin,command);
	
		if(command.find(" -i ")!=string::npos && command.find(" -t ")!=string::npos)
			tryagain = false;
	}
	
	fileName = command.substr(12,13);
	read_start_clk = clock();
	readData(fileName,a);//reading file
	read_end_clk = clock();
	
	if(command[29]=='b'){//select task
		buildMaxHeap(a);
		is_buildheap=true;
		writeData(fileName,a);//writing to a file
	}else{
		sort_start_clk = clock();
		heapsort(a);
		sort_end_clk = clock();		
		write_start_clk = clock();
		writeData(fileName,a);//writing to a file
		write_end_clk= clock();

		int readtime=(read_end_clk-read_start_clk)*100/CLOCKS_PER_SEC;
		int sorttime=(sort_end_clk-sort_start_clk)*100/CLOCKS_PER_SEC;
		int writetime=(write_end_clk-write_start_clk)*100/CLOCKS_PER_SEC;
		writeTime(command,readtime,sorttime,writetime);//writing to time.txt
	}
	//getchar();
   return 0; 
} 

void readData( string fileName, int *a)
{
	ifstream infile ("input/"+fileName);//open file

	if(!infile.is_open())
		cout << "Unable to open file"<<endl; 

	else{
		while(infile >> a[length])//read numbers
			length++;
		length--;

		infile.close();
	}
}

void writeData(string fileName, int *a)
{
	ofstream outfile;
	mkdir("./output");
	
	if(is_buildheap)
		outfile.open ("output/"+fileName.substr(0,9)+"_b.txt");//open output file for buildMaxHeap
	else
		outfile.open ("output/"+fileName.substr(0,9)+"_s.txt");//open output file for heapsort

	int i=1;

	if (!outfile.is_open())
		cout << "Unable to open file"<<endl;
		
	else{
		while(i<=length)
			outfile << a[i++] << endl;//writing to the file

		outfile.close();
	} 
}

void heapsort(int *a){
	buildMaxHeap(a);
	for(int i=length; i > 1; i--){
		int tmp = a[1];
		a[1] = a[i];
		a[i] = tmp;
		heapSize--;
		max_heapify(a,1);
	}
}

void buildMaxHeap(int* a){
	heapSize=length;
	for(int i=length/2; i > 0; i--)
		max_heapify(a,i);
}

void max_heapify(int* a,int i){
	int left = i*2;
	int right = left + 1;
	int largest;
	
	if(left <= heapSize && a[left] > a[i])
		largest = left;
	else
		largest = i;
	if(right <= heapSize && a[right] > a[largest])
		largest = right;

	if(largest != i){
		int tmp = a[i];
		a[i] = a[largest];
		a[largest] = tmp;
		max_heapify(a,largest);
	}
}

void writeTime(string command, int read, int sort, int write)
{
	ofstream outfile("output/time.txt", ios::out | ios::app); //open new file or existing file
	
	if (!outfile.is_open())
		cout << "Unable to open file"<<endl;
		
	else
		outfile << command << "\t" <<read << "\t" << sort << "\t" << write<< endl;//append to the file
	
	outfile.close();
}



