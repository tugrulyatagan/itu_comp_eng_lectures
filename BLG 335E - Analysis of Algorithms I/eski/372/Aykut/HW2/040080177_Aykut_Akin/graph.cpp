/********************************************************************************
*	Name Surname: Aykut Akin													*
*	Number		: 040080177														*
*	Due Date	: 23.03.2011													*
*																				*
*	Every information about functions and classes can be found in report		*
*																				*
*********************************************************************************/

#include "graph.h"
#include <algorithm>

Graph::Graph(string fileName){	
	total = 0;
	totalmst = 0;
	readData(fileName);
}

Graph::~Graph(){}

void Graph::clear(){
	totalmst = 0;
	mst.clear();
}

void Graph::readData(string fileName){
	
	ifstream infile (fileName.c_str());//open file
	
	int i=0;
	if(!infile.is_open())
		cout << "Unable to open file"<<endl; 

	else{
		while(!infile.eof()){

			if(i==0){//reading m
				infile >> m;
				i++;
			}
			
			else if(i==1){//reading n
				infile >> n;
				i++;
			}

			else{//reading edges
				if(i<n+2){
					Edge* edge = new Edge;
					infile >> edge->node1;
					infile >> edge->node2;
					infile >> edge->weight;
					total += edge->weight;
					edges.push_back(edge);
					i++;
				}

				else
					infile >> i;
			}
		}
		
		infile.close();
	}
}

bool sortFunc (Edge* e1, Edge* e2){ return e1->weight < e2->weight;}
bool sortFunc2 (Edge* e1, Edge* e2){ return e1->node1 < e2->node1;}
bool sortFunc3 (Edge* e1, Edge* e2){ return e1->node2 < e2->node2;}

void Graph::writeData(int time){

	ofstream outfile("cityplan_optimized.txt");			

	if (!outfile.is_open())
		cout << "Unable to open file"<<endl;

	else{
		sort(mst.begin(), mst.end(), sortFunc2);//sort edges according to sortFunc function
		sort(mst.begin(), mst.end(), sortFunc3);
		for(int i=0; i<mst.size(); i++){
			outfile << mst[i]->node1;
			outfile << "\t";
			outfile << mst[i]->node2;
			outfile << endl;	
		}

		outfile << "Total savings: " << total - totalmst << " AOALiras" << endl << endl;
		outfile << "Total gain:( " << totalmst << " / " << total << " ) " << static_cast<float>(totalmst) / static_cast<float>(total) * 100.0 << " %" << endl << endl;
		outfile << "Running time: " << time << " ms";
		outfile.close();
	} 
}

void Graph::kruskal(){

	int *cycles = new int[m];

	vector<Edge*> edgescopy = edges; //not to loose original graph
	
	sort(edgescopy.begin(), edgescopy.end(), sortFunc);//sort edges according to sortFunc function

	for(int i=0; i<m; i++) 
		cycles[i] = i;

    while(mst.size()<(m-1) && edgescopy.size()){//if mst did not reach the maximum size and there is still edge in graph
      
		if(cycles[edgescopy[0]->node1]!=cycles[edgescopy[0]->node2]){//if there is no cycle
			
			for(int i=0; i<m; i++){//for all nodes
				if(cycles[i]==cycles[edgescopy[0]->node2])
					cycles[i] = cycles[edgescopy[0]->node1];//rearrange cycles(write the oldest connected edge)
			}
		
			mst.push_back(edgescopy[0]);//add to mst
		}

		edgescopy.erase(edgescopy.begin(),edgescopy.begin()+1);//delete checked edge
    }

    for(int i=0;i<mst.size();i++)
		totalmst += mst[i]->weight;
    
}