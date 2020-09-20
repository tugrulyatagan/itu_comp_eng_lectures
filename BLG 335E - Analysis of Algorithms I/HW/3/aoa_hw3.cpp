//============================================================================
// Name          : aoa_hw3.cpp
// Author        : Tugrul Yatagan
// Student Number: 040100117
// Lecture       : BLG335E, Analysis of Algorithms I, Fall 2013
// Subject       : Linear Probing, Double Hashing, Universal Hashing
//============================================================================

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <time.h>

using namespace std;

#define INSERTFILE "insert.txt" // input insert file name
#define SEARCHFILE "search.txt" // input search file name

void insert_linear(int); // insert linear probing hash table function
void search_linear(const char*); // search from file in linear hash table
bool search_linear_key(int); // search one element in linear hash table

void insert_double(int); // insert double hashing hash table function
void search_double(const char*);  // search from file in double hash table
bool search_double_key(int); // search one element in double hash table

void insert_universal(int); // insert universal hashing hash table function
void search_universal(const char*);  // search from file in universal hash table
bool search_universal_key(int); // search one element in universal hash table

int *insert_set; // insert set, read from insert file
int m; // hash table size
int collisions = 0; // collisions number, used for all methods

int *linear_hash_table; // array of linear hashing table
int *double_hash_table; // array of double hashing table
int *universal_hash_table; // array of universal hashing table
int *a; // array of random a numbers for universal hashing function

int main(int argc, char* argv[]) {
	srand(time(NULL));

	if (argc != 2) { // there must be 2 arguments
		cerr << "Invalid arguments Please give only one integer m argument." << endl;
		return -1;
	}
	m = atoi(argv[1]); // take m value from command line

	string line;
	ifstream insertFile(INSERTFILE, ifstream::in); // read insert set from file
	if (insertFile.is_open()) {
		int insert_line_number = 0;
		while (getline(insertFile, line)) // find number of lines
			insert_line_number++;

		if (insert_line_number > m) {
			cerr << "m is smaller than insert set" << endl;
			return -1;
		}
		cout << "m: " << m << endl;

		insertFile.clear();
		insertFile.seekg(0, insertFile.beg); // set cursor to beginning of the file

		insert_set = new int[insert_line_number]; // create an array which will consist of insert elements
		for (int j = 0; getline(insertFile, line); j++) {
			insert_set[j] = atoi(line.c_str());
		}
		insertFile.close(); // close insert file

		insert_linear(insert_line_number); // insert linear probing hash table
		search_linear(SEARCHFILE); // search linear probing in linear hash table

		insert_double(insert_line_number); // insert double hashing hash table
		search_double(SEARCHFILE); // search double hashing in double hash table

		insert_universal(insert_line_number); // insert universal hashing hash table
		search_universal(SEARCHFILE); // search universal hashing in universal hash table

		delete[] insert_set;
		delete[] linear_hash_table;
		delete[] double_hash_table;
		delete[] universal_hash_table;
		insertFile.close();
	} else {
		cerr << "Input file " << INSERTFILE << " could not be opened." << endl;
		return -1;
	}

	return 0;
}

void insert_linear(int insert_line_number) {
	linear_hash_table = new int[m];
	for (int i = 0; i < m; i++) {
		linear_hash_table[i] = -1; // fill hash table with sentinel values
	}
	collisions = 0; // reset collision value
	for (int j = 0; j < insert_line_number; j++) {
		int k = insert_set[j];
		for (int i = 0; i < m; i++) {
			int pos = (k + i) % m; // linear probing hash function
			if (linear_hash_table[pos] == -1) { // if slot is empty
				linear_hash_table[pos] = k; // insert element
				collisions += i;
				break;
			}
		}
	}
	cout << "Linear insertion collision number   : " << collisions << endl;
}

void search_linear(const char* search_file_name) {
	string line;
	ifstream searchFile(search_file_name, ifstream::in);
	if (searchFile.is_open()) { // read search set from file
		collisions = 0;
		for (int j = 0; getline(searchFile, line); j++) {
			int element = atoi(line.c_str());
			if (search_linear_key(element)) { // search element
				//cout << "Found" << endl;
			} else {
				//cout << "Not Found" << endl;
			}
		}
		cout << "Linear search collision number      : " << collisions << endl << endl;
		searchFile.close();
	} else {
		cerr << "Input file " << search_file_name << " could not be opened." << endl;
	}
}

bool search_linear_key(int search) {
	for (int i = 0; i < m; i++) { // try to search element max m times
		int pos = (search + i) % m; // linear probing hash function
		if (linear_hash_table[pos] == search) { // if element is found
			collisions += i;
			return 1; // found
		} else if (linear_hash_table[pos] == -1) { // if search algorithm reaches one of the free slot
			collisions += i;
			return 0; // not found
		}
	}
	return 0;
}

void insert_double(int insert_line_number) {
	double_hash_table = new int[m];
	for (int i = 0; i < m; i++) {
		double_hash_table[i] = -1; // fill hash table with sentinel values
	}
	collisions = 0; // reset collision value
	for (int j = 0; j < insert_line_number; j++) {
		int k = insert_set[j];
		for (int i = 0; i < m; i++) {
			int pos = ((k % m) + i * (1 + (k % (m - 1)))) % m; // double hash function
			if (double_hash_table[pos] == -1) { // if slot is empty
				double_hash_table[pos] = k;  // insert element
				collisions += i;
				break;
			}
		}
	}
	cout << "Double insertion collision number   : " << collisions << endl;
}

void search_double(const char* search_file_name) {
	string line;
	ifstream searchFile(search_file_name, ifstream::in);
	if (searchFile.is_open()) {  // read search set from file
		collisions = 0;
		for (int j = 0; getline(searchFile, line); j++) {
			int element = atoi(line.c_str());
			if (search_double_key(element)) { // search element
				//cout << "Found" << endl;
			} else {
				//cout << "Not Found" << endl;
			}
		}
		cout << "Double search collision number      : " << collisions << endl << endl;
		searchFile.close();
	} else {
		cerr << "Input file " << search_file_name << " could not be opened." << endl;
	}
}

bool search_double_key(int search) {
	for (int i = 0; i < m; i++) { // try to find element max m times
		int pos = ((search % m) + i * (1 + (search % (m - 1)))) % m;  // double hash function
		if (double_hash_table[pos] == search) {  // if element is found
			collisions += i;
			return 1;  // found
		} else if (double_hash_table[pos] == -1) { // if search algorithm reaches one of the free slot
			collisions += i;
			return 0; // not found
		}
	}
	return 0;
}

void insert_universal(int insert_line_number) {
	universal_hash_table = new int[m];
	for (int i = 0; i < m; i++) {
		universal_hash_table[i] = -1;  // fill hash table with sentinel values
	}
	collisions = 0; // reset collision value

	a = new int[3]; // create random a values for universal hashing
	a[0] = rand() % (m - 1);
	a[1] = rand() % (m - 1);
	a[2] = rand() % (m - 1);

	for (int j = 0; j < insert_line_number; j++) {
		int k = insert_set[j];
		int k0 = k / 1000000; // decompose element
		int k1 = (k / 1000) % 1000;
		int k2 = k % 1000;
		for (int i = 0; i < m; i++) {
			int pos = (((a[0] * k0 + a[1] * k1 + a[2] * k2) % m) + i) % m; // universal hash function
			if (universal_hash_table[pos] == -1) {  // if slot is empty
				universal_hash_table[pos] = k;  // insert element
				collisions += i;
				break;
			}
		}
	}
	cout << "Universal insertion collision number: " << collisions << endl;
}

void search_universal(const char* search_file_name) {
	string line;
	ifstream searchFile(search_file_name, ifstream::in);
	if (searchFile.is_open()) {  // read search set from file
		collisions = 0;
		for (int j = 0; getline(searchFile, line); j++) {
			int element = atoi(line.c_str());
			if (search_universal_key(element)) {  // search element
				//cout << "Found" << endl;
			} else {
				//cout << "Not Found" << endl;
			}
		}
		cout << "Universal search collision number   : " << collisions << endl << endl;
		searchFile.close();
	} else {
		cerr << "Input file " << search_file_name << " could not be opened." << endl;
	}
}

bool search_universal_key(int search) {
	int k[3] = { (search / 1000000), ((search / 1000) % 1000), (search % 1000) }; // decompose key
	for (int i = 0; i < m; i++) {  // try to find element max m times
		int pos = (((a[0] * k[0] + a[1] * k[1] + a[2] * k[2]) % m) + i) % m;  // universal hash function
		if (universal_hash_table[pos] == search) {   // if element is found
			collisions += i;
			return 1; // found
		} else if (universal_hash_table[pos] == -1) { // if search algorithm reaches one of the free slot
			collisions += i;
			return 0; // not found
		}
	}
	return 0;
}

