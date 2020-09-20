//============================================================================
// Name			: aoa2_hw3.cpp
// Author		: Tugrul Yatagan
// Student Num	: 040100117
// Course		: BLG 372E Analysis of Algorithms HW3
// CRN			: 22853
// Lecturer		: Zehra Cataltepe
// Date			: 16.05.2014
//============================================================================

#include <iostream>
#include <fstream> 	// file operations
#include <string.h> 	// memset
#include <sstream>		// istringstream
using namespace std;

class BipartiteGraph {
	bool *traversed; // boolean array for record traversed elements
	int *matched; // integer array keeps assigned elements
	int m, n; // size of adjacency matrix also customer and apartment number
	bool augment(int); // recursive traversal function for augmentation
public:
	bool **adjacencyMatrix; // input matrix
	BipartiteGraph(int, int); // constructor takes size of adjacency matrix
	~BipartiteGraph(); // destructor
	void match(const char *, const char*); // finds maximum bipartite matches and shows results
};

BipartiteGraph::BipartiteGraph(int row, int col) {
	m = row; // set size of matrix
	n = col;

	matched = new int[n]; // memory allocation for matched array
	memset(matched, -1, n * sizeof(int)); // initialize matched array, filled with -1

	traversed = new bool[n]; // memory allocation for traversed array
	memset(traversed, 0, n * sizeof(bool)); // initialize traversed array, filled with 0

	adjacencyMatrix = new bool*[m]; // memory allocation for adjacency matrix
	for (int i = 0; i < m; i++) {
		adjacencyMatrix[i] = new bool[n];
		memset(adjacencyMatrix[i], 0, n * sizeof(bool)); // initialization for adjacency matrix, filled with 0
	}
}

BipartiteGraph::~BipartiteGraph() {
	delete[] matched;  // deallocate arrays
	delete[] traversed;
	for (int i = 0; i < m; i++) { // deallocate matrix
		delete[] adjacencyMatrix[i];
	}
	delete[] adjacencyMatrix;
}

bool BipartiteGraph::augment(int u) {
	for (int v = 0; v < n; v++) { // try all apartments for one customer v
		if (adjacencyMatrix[u][v] && !traversed[v]) { // if u can be matched with v
			traversed[v] = 1; // mark v as traversed
			if (matched[v] < 0) { // if alternative match is possible
				matched[v] = u; // mark as traversed
				return 1; // matched
			}
			if (augment(matched[v])) { // if match is possible
				matched[v] = u;  // mark as traversed
				return 1; // matched
			}
		}
	}
	return 0; // not matched
}

// calculates maximum bipartite matches, takes name of the elements
void BipartiteGraph::match(const char *applicant, const char *acceptor) {
	for (int u = 0; u < m; u++) { // traverse all graph
		memset(traversed, 0, n * sizeof(bool)); // filled traversed array with 0
		augment(u); // find if u can match
	}

	// print results as applicant -> acceptor
	cout << applicant << " -> " << acceptor << endl;
	for (int i = 0; i < m; i++) {
		cout << i + 1 << "  ->  ";
		for (int j = 0; j < n; j++) {
			if (matched[j] == i) { // find pair of i
				cout << j + 1 << endl;
				break;
			}
			if (j == n - 1) { // if matching not found
				cout << "X" << endl;
			}
		}
	}

	// print results as acceptor -> applicant
	cout << endl << acceptor << " -> " << applicant << endl;
	for (int i = 0; i < n; i++) {
		if (matched[i] != -1) {
			cout << i + 1 << "  ->  " << matched[i] + 1 << endl;
		} else {
			cout << i + 1 << "  ->  X" << endl;
		}
	}
}

int main(int argc, char* argv[]) {
	if (argc != 2) { // there must be 2 arguments
		cerr << "Invalid arguments." << endl;
		return -1;
	}
	const char *inputFileName = argv[1]; // take input file name as command line argument

	BipartiteGraph *RealEstate; // create BipartiteGraph object

	ifstream realEstateFile(inputFileName); // open file
	if (realEstateFile.is_open()) {
		string stringLine;
		int temp, customerNumber, apartmentNumber = 0;
		// first take customer and apartment number, m and n
		for (customerNumber = 0; getline(realEstateFile, stringLine);
				customerNumber++) {
			istringstream is(stringLine);
			while (is >> temp) {
				if (temp > apartmentNumber)
					apartmentNumber = temp;
			}
		}
		// get cursor to beginning of the file
		realEstateFile.clear();
		realEstateFile.seekg(0, realEstateFile.beg);

		// call constructor with m and n values
		RealEstate = new BipartiteGraph(customerNumber, apartmentNumber);

		for (int rowNumber = 0; getline(realEstateFile, stringLine); rowNumber++) { // read file line by line
			istringstream is(stringLine); // take integer values from line
			while (is >> temp) {
				RealEstate->adjacencyMatrix[rowNumber][temp - 1] = 1; // fill adjacency matrix
			}
		}
		realEstateFile.close(); // close file
	} else {
		cerr << "Input file " << inputFileName << " could not be opened." << endl;
		return -1;
	}

	RealEstate->match("Customer", "Apartment"); // call maximum bipartite graph match

	delete RealEstate; // delete object
	return 0;
}
