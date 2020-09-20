#include "BTree.h"

BTree::BTree(string folderName){
	root = new BTNode;
	root->leaf = true;
	root->n = 0;
	filename = "";
	name="./"+folderName;
	_mkdir(name.c_str());	
	_mkdir((name + "/node_1").c_str());
};

BTree::BTree(string folderName, string fileName){
	root = new BTNode;
	root->leaf = true;
	root->n = 0;
	name="./"+folderName;
	_mkdir(name.c_str());
	filename = fileName;
};

void BTree::BT_Insert(double k){
	BTNode* r = root;
	if(r->n == 199){
		BTNode* s = new BTNode;
		root = s;
		s->c[1] = r;
        BT_Split_Child(s, 1, r);
        BT_Insert_Nonfull(s, k);
	}	
	else 
		BT_Insert_Nonfull(r, k);
};

void BTree::BT_Split_Child(BTNode* x, int i, BTNode* y){	
	BTNode* z = new BTNode;
	z->leaf = y->leaf;
	z->n = 99;

	for(int j=1; j <= 99; j++)
		z->keys[j] = y->keys[j+100];

	if(!y->leaf){
		for(int j=1; j <= 100; j++)
			z->c[j] = y->c[j+100]; 
	}

	y->n = 99;

	for(int j=(x->n)+1; j >= i+1 ; j--)
		x->c[j+1] = x->c[j];

	x->c[i+1] = z;

	for(int j=(x->n); j >= i ; j--)
		x->keys[j+1] = x->keys[j];

	x->keys[i] = y->keys[100];
	x->n += 1;
};

void BTree::BT_Insert_Nonfull(BTNode* x, double k){
	int i = x->n;

	if(x->leaf){
		while(i>=1 && k < x->keys[i]){
			x->keys[i+1] = x->keys[i];
			i--;
		}

		x->keys[i+1] = k;
		x->n += 1;
	}

	else{
		while(i>=1 && k < x->keys[i])
			i--;
		i++;
		if(x->c[i]->n == 199){
			BT_Split_Child(x,i,x->c[i]);
			if(k > x->keys[i])
				i++;
		}
		BT_Insert_Nonfull(x->c[i],k);
	}
};

void BTree::writeData(BTNode* x){
	ofstream outfile;
	char buf[10];
	int j=1;

	outfile.open(name+"/node_1.txt");	

	if (!outfile.is_open())
		cout << "Unable to open file"<<endl;
		
	else{
		while(j <= x->n)		
			outfile << x->keys[j++] << endl;//writing to the file

		outfile.close();		
		j=1;

		if(!x->leaf){
			while(j <= x->n+1){
				int k=1;
				outfile.open(name+"/node_1/node_"+_itoa(j,buf,10)+".txt");	
				while(k <= x->c[j]->n)
					outfile << x->c[j]->keys[k++] << endl;
				outfile.close();
				j++;
			}	
		}	
	} 
};

void BTree::readData(){

	char buf[10];
	ifstream infile (name+"/node_1.txt");//open file
	root->n++;

	if(!infile.is_open())
		cout << "Unable to open file"<<endl; 

	else{
		while(infile >> root->keys[root->n])//read numbers
			root->n++;	
		root->n--;
		infile.close();

		int j=1;
		while(j<=root->n+1){
			BTNode* r = new BTNode;
			r->n++;
			infile.open(name+"/node_1/node_"+_itoa(j,buf,10)+".txt");
			while(infile >> r->keys[r->n])//read numbers
				r->n++;
			r->n--;
			root->c[j] = r;
			j++;
			infile.close();
		}
	}
};

void BTree::writeIntervalData(){
	
	ofstream outfile(name+"/"+filename);	
	int j=root->n+1;
	
	if (!outfile.is_open())
		cout << "Unable to open file"<<endl;
		
	else{

		if(!root->leaf){
			while(j >= 1){
				int k=root->c[j]->n;
				while(k >= 1)
					outfile << root->c[j]->keys[k--] << endl;				
				j--;
				if(j > 0)
					outfile << root->keys[j] << endl;							
			}	
		}
		else{
			j--;
			while(j >= 1)
				outfile << root->keys[j--] << endl;
		}
		outfile.close();
	} 
};