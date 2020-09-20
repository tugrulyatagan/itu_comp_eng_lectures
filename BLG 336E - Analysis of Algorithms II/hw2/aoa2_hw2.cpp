//============================================================================
// Name			: aoa2_hw2.cpp
// Author		: Tugrul Yatagan
// Student Num	: 040100117
// Course		: BLG 372E Analysis of Algorithms HW2
// CRN			: 22853
// Lecturer		: Zehra Cataltepe
// Date			: 26.04.2014
//============================================================================

#include <iostream>
#include <fstream>
#include <string.h>
#include <sstream>
#include <iomanip>

#define OUTPUT_FILE_NAME "encodedProteins.txt"
using namespace std;

//*********************
class AminoAcid { // amino acid class
	char *name;
	char abbreviatedName[4];
	int occuarenceNumber; // frequency
public:
	char *huffmanCode;
	AminoAcid(string, string); // constructor
	~AminoAcid();
	char *getName();
	char *getAbbreviatedName();
	int getCounter();
	void incrementCounter();
};

AminoAcid::AminoAcid(string n, string an) { // name, abbreviated name
	huffmanCode = NULL;
	name = new char[n.length() + 1];
	strcpy(name, n.c_str());
	strcpy(abbreviatedName, an.c_str());
	occuarenceNumber = 0;
}
AminoAcid::~AminoAcid() {
	delete name, huffmanCode;
}
char * AminoAcid::getName() {
	return name;
}
char * AminoAcid::getAbbreviatedName() {
	return abbreviatedName;
}
void AminoAcid::incrementCounter() {
	occuarenceNumber++;
}
int AminoAcid::getCounter() {
	return occuarenceNumber;
}

//**********************
class HuffmanNode { // Huffman tree node
public:
	AminoAcid *aminoAcidLeaf; // amino acid leaf pointer
	HuffmanNode *right; // right child in tree
	HuffmanNode *left; // left child in tree
	HuffmanNode *next; // next element in linked list
	int elementSum; // sum of frequency under the node
	HuffmanNode(AminoAcid *);
	HuffmanNode(HuffmanNode *, HuffmanNode *);
	~HuffmanNode();
};
HuffmanNode::HuffmanNode(AminoAcid *firstElement) { // constructor for new node
	elementSum = firstElement->getCounter();
	right = NULL;
	left = NULL;
	next = NULL;
	aminoAcidLeaf = firstElement;
}
HuffmanNode::HuffmanNode(HuffmanNode *firstElement, HuffmanNode *secondElement) { // constructor for combining two node
	elementSum = firstElement->elementSum + secondElement->elementSum;
	aminoAcidLeaf = NULL;
	next = NULL;
	if (firstElement->elementSum < secondElement->elementSum) {
		left = firstElement;
		right = secondElement;
	} else {
		left = secondElement;
		right = firstElement;
	}
}
HuffmanNode::~HuffmanNode() {
	delete right, left, next, aminoAcidLeaf;
}

//**************************
class HuffmanTree { // huffman tree class
	AminoAcid *aminoAcidList; // amino acid list for building tree
	HuffmanNode *listHead; // head of linked list
	HuffmanNode *treeRoot; // root of tree
	void buildLinkedList();
	void addToLinkedList(HuffmanNode *);
	void buildTree();
	void genereteCode(); // generates huffman code
	void traverseTree(HuffmanNode *, char *, int);
public:
	HuffmanTree(AminoAcid *);
	~HuffmanTree();
	AminoAcid *encode(char *);
};

HuffmanTree::HuffmanTree(AminoAcid *l) { // constructor takes amino acid array for building tree
	aminoAcidList = l;
	treeRoot = NULL;
	buildLinkedList(); // build linked list from amino acid array
	buildTree(); // build tree from linked list
	genereteCode(); // generate huffman codes
}
HuffmanTree::~HuffmanTree() { // delete huffman tree by linked list
	delete treeRoot;
	HuffmanNode *temp = listHead;
	while(temp != NULL){
		listHead = listHead->next;
		delete temp;
		temp = listHead;
	}
}
void HuffmanTree::buildLinkedList() { // build linked list for building tree
	listHead = new HuffmanNode(&aminoAcidList[0]);
	for (int i = 1; i < 20; i++) {
		HuffmanNode *newNode = new HuffmanNode(&aminoAcidList[i]);
		addToLinkedList(newNode);
	}
}
void HuffmanTree::addToLinkedList(HuffmanNode *newNode) { // add node to linked list
	HuffmanNode *temp1 = listHead;
	HuffmanNode **temp2 = &listHead;

	while (temp1 != NULL && (temp1->elementSum < newNode->elementSum)) {
		temp2 = &temp1->next;
		temp1 = temp1->next;
	}
	newNode->next = temp1;
	*temp2 = newNode;
}

void HuffmanTree::buildTree() { // build huffman tree from linked list
	while (listHead->next != NULL) { // while list is not finish
		HuffmanNode *newNode = new HuffmanNode(listHead, listHead->next);
		addToLinkedList(newNode);
		treeRoot = newNode;
		listHead = listHead->next->next; // remove from linked list
	}
}
void HuffmanTree::genereteCode() { // generate huffman codes
	char code[64] = "";
	int top = 0;
	traverseTree(treeRoot, code, top);

}
void HuffmanTree::traverseTree(HuffmanNode *r, char *code, int top) {
	// traverse huffman tree for generating huffman code
	if (r->left) { // parent
		code[top] = '0';
		traverseTree(r->left, code, top + 1);
	}
	if (r->right) { // parent
		code[top] = '1';
		traverseTree(r->right, code, top + 1);
	}
	if (r->aminoAcidLeaf != NULL) { // leaf
		char *aminoAcidCode = new char[top];
		aminoAcidCode[top] = '\0';
		strncpy(aminoAcidCode, code, top);
		r->aminoAcidLeaf->huffmanCode = aminoAcidCode;
	}
}
AminoAcid *HuffmanTree::encode(char *find) { // encode huffman code
	HuffmanNode *temp = treeRoot;
	for (int i = 0; find[i] != '\0'; i++) {
		if ((find[i] == '0') && (temp->left != NULL)) {
			temp = temp->left;
		} else if ((find[i] == '1') && (temp->right != NULL)) {
			temp = temp->right;
		} else {
			return NULL;
		}
	}
	if (temp->aminoAcidLeaf) {
		return temp->aminoAcidLeaf;
	} else {
		return NULL;
	}
}

//**************************
class LookupNode {
	char letter; // letter of node
public:
	AminoAcid *leaf;
	LookupNode *children[30]; // children of nodes, 30 letter
	LookupNode(char);
	LookupNode(char, AminoAcid *);
	~LookupNode();
	LookupNode *findChild(char); // search child
};
LookupNode::LookupNode(char newChar) { // constructor for internal node
	leaf = NULL;
	letter = newChar;
	for (int i = 0; i < 30; i++) {
		children[i] = NULL;
	}
}
LookupNode::LookupNode(char newChar, AminoAcid * newLeaf) { // constructor for leaf
	leaf = newLeaf;
	letter = newChar;
}
LookupNode::~LookupNode() {
	delete leaf;
	delete *children;
}
LookupNode *LookupNode::findChild(char search) { // search child
	int index = search - 'a';
	if (children[index] != NULL) {
		return children[index];
	}
	return NULL;
}

//**********************
class LookupTable {
	LookupNode *lookupRoot; // lookup table trie root
public:
	void addWord(char *, AminoAcid *); // add word to trie
	char *findCode(char *); // find code in tree
	LookupTable(AminoAcid *);
	~LookupTable();
};
LookupTable::LookupTable(AminoAcid *l) { // build trie from amino acid array
	lookupRoot = new LookupNode(' ');
	for (int i = 0; i < 20; i++) {
		addWord(l[i].getAbbreviatedName(), &l[i]);
	}
}
LookupTable::~LookupTable() {
	delete lookupRoot;
}
void LookupTable::addWord(char *w, AminoAcid *leaf) { // add word to trie
	LookupNode *temp = lookupRoot;
	for (int i = 0; i < 3; i++) {
		if (temp->findChild(w[i]) != NULL) {
			temp = temp->findChild(w[i]);
		} else {
			int newChildIndex = w[i] - 'a';
			if (i == 2) {
				LookupNode *newNode = new LookupNode(w[i], leaf);
				temp->children[newChildIndex] = newNode;
				temp = temp->findChild(w[i]);
			} else {
				LookupNode *newNode = new LookupNode(w[i]);
				temp->children[newChildIndex] = newNode;
				temp = temp->findChild(w[i]);
			}
		}
	}
}
char *LookupTable::findCode(char *find) { // search code in the trie
	LookupNode *temp = lookupRoot;
	char *err = new char(sizeof "NOT FOUND");
	strcpy(err, "NOT FOUND");
	for (int i = 0; i < 3; i++) {
		if (temp->findChild(find[i]) != NULL) {
			temp = temp->findChild(find[i]);
		} else {
			return err;
		}
	}
	return temp->leaf->huffmanCode;
}

//**********************
int main(int argc, char* argv[]) {
	if (argc != 2) { // there must be 2 arguments
		cerr << "Invalid arguments." << endl;
		return -1;
	}
	const char *proteinsFileName = argv[1];

	// basic amino acids array
	AminoAcid aminoAcids[20] = { AminoAcid("Alanine", "ala"), AminoAcid(
			"Arginine", "alg"), AminoAcid("Asparagine", "asn"), AminoAcid(
			"Aspartic acid", "asp"), AminoAcid("Cysteine", "cys"), AminoAcid(
			"Leucine", "leu"), AminoAcid("Lysine", "lys"), AminoAcid(
			"Methionine", "met"), AminoAcid("Phenylalanine", "phe"), AminoAcid(
			"Proline", "pro"), AminoAcid("Glutamic acid", "glu"), AminoAcid(
			"Glutamine", "gln"), AminoAcid("Glycine", "gly"), AminoAcid(
			"Histidine", "his"), AminoAcid("Isoleucine", "ile"), AminoAcid(
			"Serine", "ser"), AminoAcid("Threonine", "thr"), AminoAcid(
			"Tryptophan", "thp"), AminoAcid("Tyrosine", "tyr"), AminoAcid(
			"Valine", "val") };

	int totalAminoacidNumber = 0;
	ifstream proteinsFile(proteinsFileName);
	if (proteinsFile.is_open()) { // read input file
		string stringLine;
		string buf;

		while (getline(proteinsFile, stringLine)) { // find occurrence number of amino acids
			stringstream ss(stringLine);
			while (ss >> buf) {
				for (int i = 0; i < 20; i++) { // find amino acid
					if (buf.compare(aminoAcids[i].getAbbreviatedName()) == 0) {
						aminoAcids[i].incrementCounter();
						totalAminoacidNumber++;
						break;
					}
				}
			}
		}
		proteinsFile.close();
	} else {
		cerr << "Input file " << proteinsFileName << " could not be opened." << endl;
		return -1;
	}

	HuffmanTree Tree(aminoAcids); // build huffman tree

	cout << left << setw(15) << "AMINO ACID" << setw(5) << "ABBR" << setw(5) << "FREQ" << "CODE" << endl;
	cout << "-------------------------------" << endl;
	for (int i = 0; i < 20; i++) { // print amino acids
		cout << left << setw(15) << aminoAcids[i].getName();
		cout << left << setw(5) << aminoAcids[i].getAbbreviatedName();
		cout << setw(5) << aminoAcids[i].getCounter();
		cout << aminoAcids[i].huffmanCode << endl;
	}

	LookupTable Table(aminoAcids); // build lookup table

	int totalBits = 0;
	proteinsFile.open(proteinsFileName);
	ofstream outputFile(OUTPUT_FILE_NAME); // read input file again for proteins
	if (proteinsFile.is_open()) {
		if (outputFile.is_open()) {
			string stringLine;
			string buf;
			char *code;

			while (getline(proteinsFile, stringLine)) { // read protein
				stringstream ss(stringLine);
				while (ss >> buf) { // write code of protein to output file
					code = Table.findCode(strdup(buf.c_str()));
					totalBits += strlen(code);
					outputFile << code; // write code of amino acid
				}
				outputFile << endl;
			}
			outputFile.close();
			cout << endl << "Output results writed to " << OUTPUT_FILE_NAME << endl;
		} else {
			cerr << "Output file " << OUTPUT_FILE_NAME << " could not be opened." << endl;
			return -1;
		}
		proteinsFile.close();
	} else {
		cerr << "Input file " << proteinsFileName << " could not be opened." << endl;
		return -1;
	}

	float totalBitsNoHuffman = 5 * totalAminoacidNumber;
	cout << endl <<  "Total amino acid number: " << totalAminoacidNumber << endl;
	cout << "Fixed lenght needed total bit number: 5 x " << totalAminoacidNumber << " = ";
	cout << 5 * totalAminoacidNumber << " bits" << endl;
	cout << "Huffman coding total bit number: " << totalBits << " bits" << endl;
	cout << "Compression rate: ";
	cout << ((totalBitsNoHuffman - totalBits) * 100) / totalBitsNoHuffman << "%" << endl;

	char input[10];
	cout << endl << "Enter binary input for decode amino acid or ";
	cout << "enter 'exit' for terminate the program." << endl;
	while (1) { // take input from terminal
		cout << "> ";
		cin >> input;
		if (!strcmp(input, "exit")) {
			break;
		}
		AminoAcid *search = Tree.encode(input); // encode input
		if (search) {
			cout << left << setw(15) << search->getName();
			cout << left << setw(5) << search->getAbbreviatedName();
			cout << setw(5) << search->getCounter() << endl;
		} else {
			cout << "NOT FOUND" << endl;
		}
	}
	cout << endl << "Program terminated." << endl << endl;

	return 0;
}
