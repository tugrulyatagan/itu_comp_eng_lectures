#include "BTree.h"


void toLowerCase(string &str){
	/*
	* This function takes one string parameter and make its all character lower case.
	*/
	for(int i=0; i < str.length(); i++)
		str[i] = tolower(str[i]);
}

string findPlace(int sentence, int column){
	/*
	* This function takes two integer which are the words' column and row values.
	* According to these values, creates one string for holding these words' places
	*/
		string s;
		char buffer[5];

		s += "(";

		itoa (column,buffer,10);		
		for(int i=0; buffer[i]!='\0'; i++)
			s += buffer[i];

		s += ",";
		
		itoa (sentence,buffer,10);		//parameter of 10 means it is decimal.
		for(int i=0; buffer[i]!='\0'; i++)
			s += buffer[i];

		s += ")";

	return s;		
}
	
BTree::BTree(int order){
	/*
	* This function is the constructor of B-Tree class.
	* In this function, standard BTree constructor algorithm is used
	*/
	m = order;						
	Node *temproot = new Node(m);
	temproot->n = 0;
	temproot->c = NULL;
	temproot->leaf = true;
	root = temproot;
}

string BTree::readWord(string fileName, int s, int c){
	/*
	* Takes fileName to read, and two integers.
	* According to these two integers, finding the word in the place s. sentence & c.column
	* and returning it back
	*/
	string line;
	const char *cumle;
	string yenicumle[100], place[100];
	int column; 

	ifstream dosya;
	dosya.open(fileName, ios::in);
	if(!dosya.fail()){
		for(int i=1; i<=s; i++)			//Read since given "s" parameter
				getline(dosya,line);

			cumle = line.c_str();
			int j=1;
			column = 0;
			for(int i=0; cumle[i]!='\0'; i++){					
				if((cumle[i]!=' ') && (cumle[i]!=',') && (cumle[i]!=';') && (cumle[i]!=':') && (cumle[i]!='\'') && (cumle[i]!='-')
					&&(cumle[i]!='!') && (cumle[i]!='?') && (cumle[i]!='.') ) 
					yenicumle[j]+=cumle[i];
				if(cumle[i]==' '){
					column++;
					place[j] = findPlace(s, column);
					j++;
				}
			}
			place[j] = findPlace(s, column +1);
			for(int i=0; i<=j; i++){
				toLowerCase(yenicumle[i]);
				}	
	}
	dosya.close();
	return yenicumle[c];	//return c column of the sentence
}


int BTree::read(string fileName){
	/*
	* This function reads data from file which name is given by fileName parameter.
	* These read datas are firstly cleaning from punctuation and later adding B-Tree
	*/
	
	string line;
	const char *cumle;
	string yenicumle[100], place[100];
	int sentence=0, column=0;

	ifstream dosya;			//For input file
	ofstream dosya2;		//For output file

	dosya.open(fileName, ios::in);
	dosya2.open(writeFileName);		

	if(!dosya.fail() && !dosya2.fail()){		//If two files can be opened without any error
		while(!dosya.eof()){
				sentence++;
				getline(dosya,line);
		//		cout<<line;
				cumle = line.c_str();
				int j=0;
				column = 0;
				for(int i=0; cumle[i]!='\0'; i++){					
					if((cumle[i]!=' ') && (cumle[i]!=',') && (cumle[i]!=';') && (cumle[i]!=':') && (cumle[i]!='\'') && (cumle[i]!='-')
						&&(cumle[i]!='!') && (cumle[i]!='?') && (cumle[i]!='.') ) 
						yenicumle[j]+=cumle[i];
					if(cumle[i]==' '){
						column++;
						place[j] = findPlace(sentence, column);
						j++;
					}
				}
				place[j] = findPlace(sentence, column +1);
				for(int i=0; i<=j; i++){
					toLowerCase(yenicumle[i]);
					B_TREE_INSERT(yenicumle[i], place[i]);
					dosya2 << yenicumle[i] <<" ";	//write the string into the output(dosya2)
					yenicumle[i].clear();
				}
				dosya2 << endl;		//Write next line into the output
		}
	}
	dosya.close();		//All works are finished about input file(dosya)
	dosya2.close();		//All works are finished about output file(dosya2)

	return sentence;	//return number of sentence back
}

NodeData BTree::B_TREE_SEARCH(Node *x, string k){
	int i=1;
	NodeData n;  // For returning empty NodeData

	while(i<= x->n && strcmp(k.c_str(), x->nd[i].data.c_str())==1)	//strcmp::= if k>data, then returns 1 
		i++;

	if(i<= x->n && strcmp(k.c_str(), x->nd[i].data.c_str()) == 0 )	//strcmp::= if k=data, then returns 0
		return x->nd[i];

	else if(x->leaf)
		return n;	//n is empty(NIL)

	else
		return B_TREE_SEARCH(x->c[i], k);
}

void BTree::B_TREE_INSERT(string k, string p){
	/*
	* This is standard B_TREE_INSERT function except 2 string parameters;
	* 1.string for the word
	* 2.string for the word's place
	*/
	Node *r = root;
	if(r->n == 2*m-1){
		Node *s = new Node(m);
		root = s;
		s->leaf = false;
		s->n = 0;
		s->c[1] = r;
        B_TREE_SPLIT_CHILD(s, 1);
        B_TREE_INSERT_NONFULL(s, k, p);
	}	
	else 
		B_TREE_INSERT_NONFULL(r, k, p);
}

void BTree::B_TREE_INSERT_NONFULL(Node *x, string k, string p){
	/*
	* This is standard(a little bit upgraded) B_TREE_INSERT_NONFULL function except 2 string parameters;
	* 1.string for the word
	* 2.string for the word's place
	*/
	int i = x->n;		
	int j = i;		//temp variable

	if(x->leaf){
		while(j>=1 && (strcmp(x->nd[j].data.c_str(), k.c_str())==1)){	//Firstly, looping for j value and if the while loop is finished
			j--;														//comparing the last data with the new string k
		}
	
		if(strcmp(k.c_str(), x->nd[j].data.c_str()) == 0){		//If the word especially is adding before
			x->nd[j].insertData(p);							//Then only add the new place to this
			return;
		}

		while(i>=1 && (strcmp(x->nd[i].data.c_str(), k.c_str())==1)){	//Now standard algorithm follows
			x->nd[i+1].assign(x->nd[i]);
			i--;
		}

		x->nd[i+1].create(k,p);		//create (i+1).data with given k,p parameters
		x->n += 1;
		
	}

	else{
		while(i>=1 && strcmp(x->nd[i].data.c_str(), k.c_str())==1)
			i--;
		i++;
		
		if(strcmp(k.c_str(), x->nd[i-1].data.c_str()) == 0){	//If the word especially is adding before
			 x->nd[i-1].insertData(p);							//Then only add the new place to this				
			 return;
		}

		if(x->c[i]->n == (x->t*2 -1)){
			B_TREE_SPLIT_CHILD(x,i);
			if(strcmp(k.c_str(), x->nd[i].data.c_str())==1)
				i++;
		}
		B_TREE_INSERT_NONFULL(x->c[i] ,k , p);		//If not found necessary place to insert, then call it for node's child	
	}
}

void BTree::B_TREE_SPLIT_CHILD(Node *x, int i){
	/*
	* This is standard B_TREE_SPLIT_CHILD function;
	*/	
	Node* z = new Node(x->t);
	Node *y = x->c[i];
	z->leaf = y->leaf;
	z->n = x->t -1;

	for(int j=1; j<= z->n; j++)
		z->nd[j].assign(y->nd[j + y->t]);

	if(!y->leaf){
		for(int j=1; j <= y->t; j++)
			z->c[j] = y->c[j + y->t]; 
	}
	y->n = y->t -1;

	for(int j=(x->n)+1; j >= i+1 ; j--)
		x->c[j+1] = x->c[j];

	x->c[i+1] = z;

	for(int j=(x->n); j >= i ; j--)
		x->nd[j+1].assign(x->nd[j]);

	x->nd[i].assign(y->nd[y->t]);
	x->n += 1;

}

