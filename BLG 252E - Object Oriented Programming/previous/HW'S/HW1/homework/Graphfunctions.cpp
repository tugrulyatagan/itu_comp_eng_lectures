#include "Graph.h"
#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;
Graph::Graph(){
	numNodes=0;
	numEdges=0;
	nodes=NULL;
	cout << "Enter your graph name: ";
	cin >> name;
	graphCount++;
}

Graph::Graph(int num){
	string nodename;
	numEdges=0;
	numNodes=0;
	nodes=NULL;

	cout << "Enter your graph name: ";
	cin >> name;
	
	for(int i=0;i<num;i++){
		cout << "Enter your node name: ";
		cin >> nodename;
		newNode(nodename);
	}
	graphCount++;
}

void Graph::intersect(const Graph &second){
	int i,j;
	cout << "Intersection of Graphes " <<name<<" & "<<second.name<<endl; 
	cout << "----------------------------------"<<endl;
	for(i=0;i<numNodes;i++){
		for(j=0;j<second.numNodes;j++){
			if((nodes[i].getName()).compare((second.nodes[j]).getName())==0){
				cout << nodes[i].getName() <<" "; 
			}
		}
	}	
	cout<<endl<<endl;
}

void Graph::unite(const Graph &second){
	string *uniongraph=new string;
	string *temp;
	int k1=0,i,j,n,flag=0;
	cout << "Union of Graphes " <<name<<" & " <<second.name<<endl; 
	cout << "----------------------------------"<<endl;
	
	for(i=0;i<numNodes;i++){//ilk grafta olup ikincisinde olmayanlar
		for(j=0;j<second.numNodes;j++){
			if((nodes[i].getName()).compare((second.nodes[j]).getName())==0){
				flag=1;
				break;
				}
			}
			if(flag!=1){
				temp=new string[++k1];
				
				for(n=0;n<k1-1;n++)//dugumleri geciciye at
					temp[n]=uniongraph[n];
					temp[n]=nodes[i].getName();
					uniongraph= new string[k1];
    
				for(n=0;n<k1;n++)//gecicideki dugumleri dugumlere at
					uniongraph[n]=temp[n];
	
				delete []temp;
		}
		flag=0;
	}
	string *unionlast=new string[k1+(second.numNodes)];
	for(i=0;i<k1;i++)
		unionlast[i]=uniongraph[i];
	for(j=0;j<second.numNodes;j++)
		unionlast[i++]=(second.nodes[j]).getName();
	for(i=0;i<k1+(second.numNodes);i++)
		cout<<unionlast[i]<<" ";
	cout<<endl<<endl;
}

Graph::Graph(const Graph &copy){
	cout << "Enter your copy graph name: ";
	cin >> name;
	numNodes=copy.numNodes;
	numEdges=copy.numEdges;
	nodes=new Node[numNodes];
	for(int i=0;i<numNodes;i++)
		nodes[i]=copy.nodes[i];
	cout<<"Graph "<<copy.name<<" has copied to " <<name <<endl;
	graphCount++;
}

string Graph::printGraph(){
	cout<<"Printing Graph "<<name<<endl;
	cout<<"-------------------"<<endl;
	for(int i=0;i<numNodes;i++){
		cout << "Node: "<<nodes[i].getName() << endl;
		for(int j=0;j<nodes[i].numEdges;j++)
				cout <<"\t Adjacents: "<< (nodes[i].getAdjacents()[j])->getName() << endl;
	}
	cout<<endl;
	return nodes[0].getName();
}

Graph::~Graph(){
	graphCount--;
	cout<<"Graph "<< name <<" has been deleted"<<endl;
}

bool Graph::newNode(string nodeName){
    int i=0,j,flag=0;
	
	for(j=0;j<numNodes;j++){
		if(nodes[j].getName()==nodeName)
			flag=1;
	}

	if(flag==0){
		Node* temp=new Node[++numNodes];//dugum sayisinin bir fazlasi yer al

		for(i=0;i<numNodes-1;i++)//dugumleri geciciye at
			temp[i]=nodes[i];				

	    temp[i]=Node(nodeName);//yeni dugumu geciciye at
	    nodes= new Node[numNodes];
    
	   for(i=0;i<numNodes;i++)//gecicideki dugumleri dugumlere at
		   nodes[i]=temp[i];

		 delete []temp;
		 cout<<"Node "<<nodeName<<" has been added to "<< name<<endl;
		 return true;
	}
	else
	{
		cout<<"There is a node with the same name "<<nodeName <<". So the node can't be added to "<<name<<endl;	
		return false;
	}
}

bool Graph::newEdge(string first,string second){
	int i,j,flag1=0,flag2=0;
		
	for(i=0;i<numNodes;i++){//kenarin birinci eklenecegi dugumu bul
		if(first.compare(nodes[i].getName())==0){
			flag1=1;
			break;
		}
	}

	for(j=0;j<numNodes;j++){//kenarin eklenecegi ikinci dugumu bul
		if(second.compare(nodes[j].getName())==0){
			flag2=1;
			break;
		}
	}
	
	if(flag1==1 && flag2==1){
		nodes[i].addAdjacent(nodes[j]);//birinci dugum icin ikinci dugumu komsu ekle
		nodes[j].addAdjacent(nodes[i]);//ikinci dugum icin birinci dugumu komsu ekle
		
		numEdges++;
		cout<<"Edge " << nodes[i].getName()<<"-"<<nodes[j].getName()<<" has been added to "<<name<<endl;
		return true;
	}

	else{
		if(flag1==0)
			cout<<"Node "<< first<<" is absent. So the edge can't be added to "<<name<<endl;
		if(flag2==0)
			cout<<"Node "<< second<<" is absent. So the edge can't be added to "<<name<<endl;
		return false;
	}
}

Node* Graph::deleteNode(string delnode){
int i ,j,dugum,flag=0;
	
	for(dugum = 0; dugum < numNodes; dugum++){//silinecek dugumu bul
		if(delnode.compare(nodes[dugum].getName())==0){
			flag=1;
			break;
			}
		}
	if(flag==1){
	for(j=0; j<nodes[dugum].numEdges; j++)//komsulardan dugumun komsulugunu kaldir
		nodes[dugum].delAdjacent((nodes[dugum].getAdjacents()[j])->getName());
	
	for(i=0; i<numNodes; i++){//komsulardan dugumun komsulugunu kaldir
		for(j=0; j<nodes[i].numEdges; j++){
			if((nodes[i].getAdjacents()[j])->getName()==delnode)
				nodes[i].delAdjacent((nodes[i].getAdjacents()[j])->getName());
		}
	}

	Node* temp = new Node[--numNodes];//komsu sayisinin bir eksigi yer al
	j=0;
		for(i = 0; i < numNodes+1; i++){		
			if(delnode==nodes[i].getName())
				continue;
						
			else{
				temp[j]=nodes[i];
				j++;
			}
		}
		
	nodes = new Node[numNodes];
		
		for(i = 0 ; i < numNodes ; i++) 
			nodes[i] = temp[i];//komsulari geciciye at
		
	delete []temp;
	cout<<"Node "<< delnode <<" is deleted from " << name<<endl;
	return nodes;
	}
	else{
		cout<<"Node "<<delnode<< " is absent. So the node can't be deleted from "<<name <<endl;
		return NULL;		
	}
}

bool Graph::deleteEdge(string first,string second){
int j,k,flag1=0,flag2=0;

	for(j = 0; j < numNodes; j++){//silinecek kenarin ilk dugumunu bul
		if(first.compare(nodes[j].getName())==0){
			flag1=1;
			break;
		}
	}
		
	for(k = 0; k < numNodes; k++){//silinecek kenarin ikinci dugumunu bul
		if(second.compare(nodes[k].getName())==0){
			flag2=1;
			break;
		}
	}
	if(flag1=1 && flag2==1){	
		nodes[j].delAdjacent(nodes[k].getName());
		nodes[k].delAdjacent(nodes[j].getName());

		numEdges--;
		cout<<"Edge "<< nodes[j].getName()<<"-"<<nodes[k].getName()<<" is deleted from "<<name <<endl;
		return true;
	}

	else{
		if(flag1==0)
			cout<<"Node "<< nodes[j].getName()<<" is absent. So the edge can't be deleted from "<<name<<endl;
		if(flag2==0)
			cout<<"Node "<< nodes[k].getName()<<" is absent. So the edge can't be deleted from "<<name<<endl;;
		return false;
	}
}

