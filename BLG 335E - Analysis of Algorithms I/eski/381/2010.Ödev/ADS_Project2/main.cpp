#include <iostream>
#include <iomanip>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <string>
#include <direct.h>
#include <vector>

using namespace std;
static int heapSize;

void readData(vector<long long> &a,string fileName,int size);
void writeData(vector<long long> &a,string fileName);
void heapsort(vector<long long> &a);
void buildMaxHeap(vector<long long> &a);
void max_heapify(vector<long long> &a,int i);
void quicksort(vector<long long> &a,int p, int r);
int randomized_partition(vector<long long> &a,int p, int r);
int partition(vector<long long> &a,int p, int r);
void radixsort(vector<long long> &a,int d);
void counting_sort(vector<long long> &a, int d);
void heapsort_start(vector<long long> &a,string command);
void quicksort_start(vector<long long> &a,string command);
void radixsort_start(vector<long long> &a,string command);
void comparesort_start(vector<long long> &a, string command);
void writeTime(string command, int sort);

/* function main begins program execution */

int main() {     
	string command;
	bool tryagain=true;

	vector<long long> a;
	a.push_back(0);

	while(tryagain){//loop until the right command

		cout << endl << "Compare all sorts: comparesorts -i data1.txt -t data1_time.txt -o data1out.txt"<<endl
		<<"Sorting the numbers with heapsort: heapsort -i data1.txt -o data1out_heap.txt"<<endl
		<<"Sorting the numbers with quicksort: quicksort -i data1.txt -o data1out_quick.txt"<<endl
		<<"Sorting the numbers with radixsort: radixsort -i data1.txt -o data1out_radix.txt"<<endl				
		<< "Please write a command: ";
		getline(cin,command);
	
		if(command.find(" -i ")!=string::npos && command.find(" -o ")!=string::npos){
			if(!command.substr(0,12).compare("comparesorts")){
				if(command.find(" -t ")!=string::npos)
					tryagain = false;
			}

			else	
				tryagain = false;		
		}
		system("cls");
	}
	
	if(!command.substr(0,8).compare("heapsort"))
		heapsort_start(a,command);
	if(!command.substr(0,9).compare("quicksort"))
		quicksort_start(a,command);
	if(!command.substr(0,9).compare("radixsort"))
		radixsort_start(a,command);
	if(!command.substr(0,12).compare("comparesorts"))
		comparesort_start(a,command);

	cout << "Islem Gerceklestirildi"<<endl;
	getchar();
   return 0; 
}

/*********************file input-output functions*********************/
void readData(vector<long long> &a,string fileName, int size){
	ifstream infile ("input/"+fileName);//open file
	long long x;
	int i=1;

	if(!infile.is_open())
		cout << "Unable to open file"<<endl; 

	else{
		if(size==-1){
			while(infile >> x)//read numbers
				a.push_back(x);			
		}
		else{
			while(infile >> x && i<=size){//read numbers
				a.push_back(x);
				i++;				
			}
		}
		infile.close();
	}
}
void writeData(vector<long long> &a,string outfileName){
	_mkdir("./output");
	ofstream outfile("output/"+outfileName);
	int i=1;

	if (!outfile.is_open())
		cout << "Unable to open file"<<endl;
		
	else{
		while(i< a.size())
			outfile << a[i++] << endl;//writing to the file

		outfile.close();
	} 
}
void writeTime(string command, int sort){
	_mkdir("./output");
	ofstream outfile; //open new file or existing file
	
	if(!command.substr(0,11).compare("comparesort"))//question 3
		outfile.open("output/" + command.substr(29,14), ios::out | ios::app);
	else	//general output
		outfile.open("output/time.txt", ios::out | ios::app);

	if (!outfile.is_open())
		cout << "Unable to open file"<<endl;
		
	if(!command.substr(0,11).compare("comparesort"))
		outfile << command.substr(59) << "\t" << sort << endl;//append to the file
	else
		outfile << command << "\t" << sort << endl;

	outfile.close();
}

/*********************heapsort functions*********************/
void heapsort_start(vector<long long> &a,string command){
	string fileName,outfileName;
	clock_t sort_start_clk, sort_end_clk; 

	fileName = command.substr(12,9);
	outfileName = command.substr(25);

	readData(a,fileName,-1);//reading file
		
	sort_start_clk = clock();
	heapsort(a);
	sort_end_clk = clock();

	writeData(a,outfileName);//writing to a file
	writeTime(command,((sort_end_clk-sort_start_clk)*100/CLOCKS_PER_SEC));//writing to time.txt
}
void heapsort(vector<long long> &a){
	buildMaxHeap(a);
	for(int i=(a.size()-1); i > 1; i--){
		long long tmp = a[1];
		a[1] = a[i];
		a[i] = tmp;
		heapSize--;
		max_heapify(a,1);
	}
}
void buildMaxHeap(vector<long long> &a){
	heapSize=a.size()-1;
	for(int i=(a.size()-1)/2; i > 0; i--)
		max_heapify(a,i);
}
void max_heapify(vector<long long> &a,int i){
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
		long long tmp = a[i];
		a[i] = a[largest];
		a[largest] = tmp;
		max_heapify(a,largest);
	}
}

/*********************quicksort functions*********************/
void quicksort_start(vector<long long> &a,string command){
	string fileName,outfileName;	
	clock_t sort_start_clk, sort_end_clk; 

	fileName = command.substr(13,9);
	outfileName = command.substr(26);

	readData(a,fileName,-1);//reading file
		
	sort_start_clk = clock();
	quicksort(a,1,(a.size()-1));
	sort_end_clk = clock();	

	writeData(a,outfileName);//writing to a file
	writeTime(command,((sort_end_clk-sort_start_clk)*100/CLOCKS_PER_SEC));//writing to time.txt
}
void quicksort(vector<long long> &a,int p, int r){
	if (p < r){
		int q = randomized_partition(a,p, r);
		quicksort(a,p,q-1);
		quicksort(a,q+1,r);
	}
}
int randomized_partition(vector<long long> &a,int p, int r){
	srand ( time(0) );
	int i = (rand() % (r-p)) + p ;
	long long tmp = a[i];
	a[i] = a[r];
	a[r] = tmp;
	return partition(a,p,r);
}
int partition(vector<long long> &a,int p, int r){
	long long x = a[r];
	int i = p-1;

	for(int j=p; j <= r-1; j++){
		if(a[j] <= x){
			i++;
			long long tmp = a[i];
			a[i] = a[j];
			a[j] = tmp;
		}
	}

	long long tmp = a[i+1];
	a[i+1] = a[r];
	a[r] = tmp;

	return i+1;
}

/*********************radixsort functions*********************/
void radixsort_start(vector<long long> &a,string command){
	string fileName,outfileName;
	clock_t sort_start_clk, sort_end_clk; 
	long long max=0;
	int digit=1;

	fileName = command.substr(13,9);
	outfileName = command.substr(26);

	readData(a,fileName,-1);//reading file		
	
	for(int i=1;i<a.size();i++){
		if(a[i]>max)
			max=a[i];
	}

	while(max=max/10)
		digit++;
		
	sort_start_clk = clock();
	radixsort(a,digit+1);
	sort_end_clk = clock();
	
	writeData(a,outfileName);//writing to a file
	writeTime(command,((sort_end_clk-sort_start_clk)*100/CLOCKS_PER_SEC));//writing to time.txt
}
void radixsort(vector<long long> &a,int d){
	for(int i=1;i<d;i++)
		counting_sort(a,i);
}
void counting_sort(vector<long long> &a, int d){
	int c[10];
	long long divider=1;
	for(int i=1;i<d;i++)
		divider *= 10;
	vector<long long> b;
	b.resize(a.size());
	for(int i=0;i<=9;i++)
		c[i]=0;
	for(int j=1;j<a.size();j++)
		c[(a[j]/divider)%10] += 1;
	for(int i=1;i<=9;i++)
		c[i] += c[i-1];
	for(int j=(a.size()-1);j>=1;j--){
		b[c[(a[j]/divider)%10]] = a[j];
		c[(a[j]/divider)%10]--;
	}
	a = b;
}

/*********************question 3*********************/
void comparesort_start(vector<long long> &a, string command){
	string fileName,outfileHeap,outfileQuick,outfileRadix;
	clock_t heap_start_clk, heap_end_clk,quick_start_clk, quick_end_clk,radix_start_clk, radix_end_clk;
	vector<long long> b;
	vector<long long> c;
	char buf[10];
	int i = 100;

	fileName = command.substr(16,9);
	outfileHeap = command.substr(47,8)+"_heap.txt";
	outfileQuick = command.substr(47,8)+"_quick.txt";
	outfileRadix = command.substr(47,8)+"_radix.txt";

	while(i<=1000000){
		readData(a,fileName,i);
		b=c=a;

		long long max=0;
		for(int j=1;j<a.size();j++){
			if(a[j]>max)
				max=a[j];
		}

		int digit=1;
		while(max=max/10)
			digit++;

		heap_start_clk = clock();
		heapsort(a);
		heap_end_clk = clock();

		quick_start_clk = clock();
		quicksort(b,1,(b.size()-1));
		quick_end_clk = clock();

		radix_start_clk = clock();
		radixsort(c,digit+1);
		radix_end_clk = clock();
		if(i==1000000){
			writeData(a,outfileHeap);//writing to a file
			writeData(b,outfileQuick);//writing to a file
			writeData(c,outfileRadix);//writing to a file
		}
		writeTime((command+"heapsort  ").append(_itoa(i, buf, 10))+": ",((heap_end_clk-heap_start_clk)*100/CLOCKS_PER_SEC));//writing to time.txt
		writeTime((command+"quicksort ").append(_itoa(i, buf, 10))+": ",((quick_end_clk-quick_start_clk)*100/CLOCKS_PER_SEC));//writing to time.txt
		writeTime((command+"radixsort ").append(_itoa(i, buf, 10))+": ",((radix_end_clk-radix_start_clk)*100/CLOCKS_PER_SEC));//writing to time.txt
		a.clear();
		a.push_back(0);

		i*=10;
	}	
}