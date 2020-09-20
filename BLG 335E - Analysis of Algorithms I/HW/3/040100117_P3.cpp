//=======================================================================
// Name           : aoa_hw3.cpp
// Author         : Tugrul Yatagan
// Student Number : 040100117
// Lecture        : BLG335E, Analysis of Algorithms I, Fall 2013
// Subject        : Linear Probing, Double Hashing, Universal Hashing
//=======================================================================

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <time.h>

#define INSERTFILE "insert.txt" // input insert file name
#define SEARCHFILE "search.txt" // input search file name

using namespace std;

class Hash {
public:
	Hash(int); // constructor for all methods
	~Hash(); // destructor for all methods
	void insert(const char*); // insert to hash table
	void search(const char*); // search elements from file in hash table
	bool search_key(int); // search one element in hash table
	virtual int hashing_function(int, int) = 0; // pure virtual hashing function, defined in lower classes
	int *hash_table; // integer array which represents hash tables
	int m; // size of hash table
	int collisions; // collisions number, used for all methods
};

class LinearHash: public Hash {
public:
	LinearHash(int m); // constructor
	int hashing_function(int, int); // linear probing hashing algorithm
};

class DoubleHash: public Hash {
public:
	DoubleHash(int m); // constructor
	int hashing_function(int, int); // double hashing algorithm
};

class UniversalHash: public Hash {
public:
	UniversalHash(int); // constructor
	~UniversalHash(); // destructor
	int hashing_function(int, int);  // universal hashing algorithm
	int *a; // array of random a numbers for universal hashing function
};

int main(int argc, char* argv[]) {
	srand(time(NULL));

	if (argc != 2) { // there must be 2 arguments
		cerr << "Invalid arguments Please give only one integer m argument." << endl;
		return -1;
	}
	int m = atoi(argv[1]); // take m value from command line
	cout << "m: " << m << endl;

	LinearHash Linear(m);
	Linear.insert(INSERTFILE); // insert elements to hash table with linear probing method
	cout << "Linear insertion collision number   : " << Linear.collisions << endl;
	Linear.search(SEARCHFILE); // search elements from file in linear hash table with linear probing method
	cout << "Linear search collision number      : " << Linear.collisions << endl << endl;

	DoubleHash Double(m);
	Double.insert(INSERTFILE); // insert elements to hash table with double hashing method
	cout << "Double insertion collision number   : " << Double.collisions << endl;
	Double.search(SEARCHFILE); // search elements from file in double hash table with double hashing method
	cout << "Double search collision number      : " << Double.collisions << endl << endl;

	UniversalHash Universal(m);
	Universal.insert(INSERTFILE); // insert elements to hash table with universal hashing method
	cout << "Universal insertion collision number: " << Universal.collisions << endl;
	Universal.search(SEARCHFILE); // search elements from file in universal hash table with universal hashing method
	cout << "Universal search collision number   : " << Universal.collisions << endl << endl;

	return 0;
}

Hash::Hash(int m) {
	Hash::m = m;
	collisions = 0;
	hash_table = new int[m];
	for (int i = 0; i < m; i++) {
		hash_table[i] = -1; // fill hash table with sentinel values
	}
}

Hash::~Hash() {
	delete[] hash_table;
}

void Hash::insert(const char* insert_file_name) {
	collisions = 0; // reset collision value

	string line;
	ifstream insertFile(insert_file_name, ifstream::in); // read insert set from file
	if (insertFile.is_open()) {
		int insert_line_number = 0;
		while (getline(insertFile, line)){ // find number of lines
			insert_line_number++;
		}

		if (insert_line_number > m) {
			cerr << "m cannot be smaller than insert element" << endl;
		}

		insertFile.clear();
		insertFile.seekg(0, insertFile.beg); // set cursor to beginning of the file

		for (int j = 0; getline(insertFile, line); j++) {
			int k = atoi(line.c_str()); // get element from file
			for (int i = 0; i < m; i++) {
				int pos = hashing_function(k, i); // find position by hash relative function
				if (hash_table[pos] == -1) { // if slot is empty
					hash_table[pos] = k; // insert element
					collisions += i;
					break;
				}
			}
		}
		insertFile.close(); // close insert file
	} else {
		cerr << "Input file " << INSERTFILE << " could not be opened." << endl;
	}
}

void Hash::search(const char* search_file_name) {
	collisions = 0; // reset collision value
	string line;
	ifstream searchFile(search_file_name, ifstream::in);
	if (searchFile.is_open()) { // read search set from file
		for (int j = 0; getline(searchFile, line); j++) {
			int element = atoi(line.c_str());
			if (search_key(element)) { // search element
				//cout << "Found" << endl;
			} else {
				//cout << "Not Found" << endl;
			}
		}
		searchFile.close();
	} else {
		cerr << "Input file " << search_file_name << " could not be opened." << endl;
	}
}

bool Hash::search_key(int search) {
	for (int i = 0; i < m; i++) { // try to search element max m times
		int pos = hashing_function(search, i); // linear probing hash function
		if (hash_table[pos] == search) { // if element is found
			collisions += i;
			return 1; // found
		} else if (hash_table[pos] == -1) { // if search algorithm reaches one of the free slot
			collisions += i;
			return 0; // not found
		}
	}
	return 0;
}

LinearHash::LinearHash(int m) :Hash(m) {
	collisions = 0; // reset collision value
}

DoubleHash::DoubleHash(int m) :Hash(m) {
	collisions = 0; // reset collision value
}

UniversalHash::UniversalHash(int m) :Hash(m) {
	collisions = 0; // reset collision value
	a = new int[3]; // create random a values for universal hashing
	a[0] = rand() % (m - 1);
	a[1] = rand() % (m - 1);
	a[2] = rand() % (m - 1);
}

int LinearHash::hashing_function(int k, int i) {
	return (k + i) % m; // linear probing hash function
}

int DoubleHash::hashing_function(int k, int i) {
	return ((k % m) + i * (1 + (k % (m - 1)))) % m; // double hash function
}

int UniversalHash::hashing_function(int k, int i) {
	int decomposed_k[3] = { (k / 1000000), ((k / 1000) % 1000), (k % 1000) }; // decompose key
	return (((a[0] * decomposed_k[0] + a[1] * decomposed_k[1] + a[2] * decomposed_k[2]) % m) + i) % m; // universal hash function
}

UniversalHash::~UniversalHash() {
	delete[] a;
}

