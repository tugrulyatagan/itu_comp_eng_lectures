#include <iostream>
#include <fstream>
#include <time.h>
#include <stdlib.h>
#include <string>

#define INPUTFILE "bids.txt" // input file name
#define OUTPUTFILE "bids_output.txt" // output file name

using namespace std;

class PQ {
	int lenght; // size of heap
	int leftChild(int); // calculates left child's index
	int rightChild(int); // calculates right child's index
	int parent(int); // calculates parents index
	void heapfy(int);
	void buildHeap(); // builds heap (used for inserting first elements)
public:
	int *A; // array which contains heap structure
	void insert(int); // insert element
	void increaseKey(int,int); // increase key value of element
	int extractMax(); // extract element which has maximum value
	PQ(int*,int); // constructor
	~PQ(); // destructor
};


int PQ::leftChild(int i){
	return (2 * i) + 1;
}

int PQ::rightChild(int i){
	return (2 * i) + 2;
}

int PQ::parent(int i){
	return (i - 1) / 2;
}

void PQ::heapfy(int i){
	int l = leftChild(i);
	int r = rightChild(i);
	int largest = i;
	if (l < lenght && A[l] > A[i]){
		largest = l;
	}
	if (r < lenght && A[r] > A[largest]){
		largest = r;
	}
	if (largest != i){
		int temp = A[largest];
		A[largest] = A[i];
		A[i] = temp;
		heapfy(largest);
	}
}

void PQ::buildHeap(){
	for (int i = (lenght - 2) / 2; i >= 0; i--){
		heapfy(i);
	}
}

void PQ::insert(int key){
	lenght++;
	A[lenght - 1] = -1000000; // negative sentinel
	increaseKey(lenght - 1, key);
}

void PQ::increaseKey(int i,int key){
	if (key < A[i]){
		cout << "New key is smaller then current key" << endl;
		return;
	}
	A[i] = key;
	while(i > 0 && A[parent(i)] < A[i]){
		int temp = A[i];
		A[i] = A[parent(i)];
		A[parent(i)] = temp;
		i = parent(i);
	}
}

int PQ::extractMax(){
	if (lenght < 1){
		cerr << "Heap underflow" << endl;
		return -1;
	}
	int max = A[0];
	A[0] = A[lenght - 1];
	lenght--;
	heapfy(0);
	return max;
}

PQ::PQ(int *input_array, int array_lenght){ // constructor
	A = input_array;
	lenght = array_lenght;
	buildHeap();
}

PQ::~PQ(){ // destructor
	delete[] A;
}


int main(int argc, char* argv[]) {
	srand (time(NULL));
	// Taking command line argument
	if (argc != 3){ // there must be 2 arguments
		cerr << "Invalid arguments." << endl;
		return -1;
	}
	int m = atoi(argv[1]);
	float p = atof(argv[2]);

	// Reading input file
	int *X = new int[m+1]; // array is allocated dynamically

	string line;
	ifstream infile (INPUTFILE);
	if(infile.is_open()){
		for (int i = 0; i < m; i++){
			getline(infile, line);
			unsigned pos = line.find("\t");
			string city_name = line.substr(0,pos);
			line = line.substr(pos+1);
			pos = line.find("\t");
			X[i] = atoi(line.substr(0,pos).c_str()); // reads line by line
		}
		infile.close();
	}
	else{
		cerr << "Input file " << INPUTFILE << " could not be opened." << endl;
		return -1;
	}

	// Auction simulation
	int winners_num = 0; // number of winners_num
	int *winners = new int[(m/100) + 1]; // list of winners
	int updates_num = 0; // number of updates_num
	int new_bids_num = 1; // number of new bids

	clock_t begin = clock();

	PQ auction(X, new_bids_num); // very first bid is used for creating heap

	for (int i = 0; i < m; i++){
		float random_prob = (rand() %100);
		random_prob /= 100;
		if (random_prob < p){ // update bid
			int random_bid = rand() % (i+1); // random bid index for update
			auction.increaseKey(random_bid, auction.A[random_bid] * 1.25); // increase %25
			updates_num++;
		}
		else{ // new bid
			auction.insert(X[new_bids_num]); // insert new bid
			new_bids_num++; // number of inserted bid
		}

		if ((i + 1) % 100 == 0){ // maximum bid is removed after every 100 bids
			winners[winners_num] =  auction.extractMax();
			winners_num++;
		}
	}

	clock_t end = clock();
	double runtime = double(end - begin);
	cout << "Running time for m = " << m << " and p = " << p << " is: " << runtime << endl << endl;

	// Writing output file
	ofstream outfile (OUTPUTFILE); // write output
	if (outfile.is_open()){
		outfile << "Running time for m = " << m << " and p = " << p << " is: " << runtime << endl << endl;
		outfile << "Number of new bids: " << new_bids_num << endl;
		outfile << "Number of updates: " << updates_num << endl;
		outfile << "Auction winners are: " << endl;
		for (int i = 0; i < winners_num; i++){
			outfile << winners[i] << endl;
		}
		outfile.close();
		cout << "Output list was written to " << OUTPUTFILE << endl << endl;
	}
	else{
		cerr << "File could not be written." << endl;
		return -1;
	}
	delete[] winners;
	return 0;
}
