/************************************************************
*	Name Surname		: Abdullah AYDEÐER					*
*   Number				: 040090533							*
*	Lecture				: Analysis of Algorithms			*
*	Lecturer			: Zehra ÇATALTEPE					*
*	Project Number		: 3									*
*	Due Date			: 21.05.2012						*
*************************************************************/
#ifndef AGENCY_H
#define AGENCY_H	//define agency once

#include <iostream>
#include <string>
#include <queue>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;
 
class Agency{
	private:
		int lastNodeNum;	//sink node determining according to the input file last line
		int totalFlow;		//Total flow that can be gone from source node to sink node
		int *nodeBeforeMe;	//for used determining the path from source to sink
		int **flows;		//two dimensional array, that says flows[1][2] from 1. agency to 2.agency flow	---same as the f(e) in the our book's algorithm
		int **capacities;   //two dimensional array, that holds capacities of all possible transitions
		void assignAll(int *, int, int);
		void read(string );	
		void readToGraph(string , int );
		bool BFS(int, int);
	public:
		Agency(string );
		~Agency();
		int getTotalFlow();
		void readFlows(string );
		void findMaxFlow(int );
		void readFlowsBeginning(string );

};

Agency::Agency(string inputName){
	/************************************************************************************
	*	Function Name	  : ---															*
	*	Aim to be written : constructor of Agency class							 		*
	*	Parameters		  : string parameter of input file name							*
	*	Return value      : ---															*
	*************************************************************************************/	
	read(inputName);	//First read necessary variables to the class parameters
	totalFlow = 0;	
	nodeBeforeMe = (int *) malloc(lastNodeNum * sizeof(int));
	assignAll(nodeBeforeMe, -1, lastNodeNum);	//all nodeBeforeMe array assigned to -1
}

Agency::~Agency(){
	/************************************************************************************
	*	Function Name	  : ---															*
	*	Aim to be written : destructor of Agency class							 		*
	*	Parameters		  : ---															*
	*	Return value      : ---															*
	*************************************************************************************/
	delete [] nodeBeforeMe;		//give allocated memories back
	for(int i = 0; i<= lastNodeNum; i++)
		delete[] flows[i];
	delete[] flows;
}

void Agency::read(string inputName){
	/********************************************************************************************
	*	Function Name	  : read																*
	*	Aim to be written : reading given input and determining last node(sink node) num		*
	*	Parameters		  : input file name														*
	*	Return value      : ---																	*
	*********************************************************************************************/
	int totalLine = 0;
	ifstream read;
	int v1, v2, v3;
	read.open(inputName.c_str(), ios::in);
		if (read.fail()) {	//if the given input file can not be opened
			 cerr << "Could not open file ";
			 cerr << inputName;
			 cerr << ".\n";
			 return;
		}
		while(!read.eof()){
			read >> v1 >> v2 >> v3;
		} 
	totalLine = v2;
	read.close();
	readToGraph(inputName, totalLine);	//call readToGraph and fill the class parameters
}

void Agency::readToGraph(string inputName, int totalLine) {
	/************************************************************************************
	*	Function Name	  : readToGraph													*
	*	Aim to be written : reading the given input file to the class parameters 		*
	*	Parameters		  : string parameter of input file name and total line for		*
	*								allocating necessary memories dynamically			*
	*	Return value      : ---															*
	*************************************************************************************/
	flows = (int **) malloc((totalLine+1) * sizeof(int *));			//allocating pointer array with size totalLine+1
	capacities = (int **) malloc((totalLine+1) * sizeof(int *));		//allocating pointer array with size totalLine+1
	if(flows == NULL  ||  capacities == NULL){	//If no enough memory
		fprintf(stderr, "out of memory\n");
		return;
	}
	for(int i=0; i<= totalLine; i++){
		flows[i] = (int *) malloc((totalLine+1) *sizeof(int));		//allocating array with size totalLine+1
		capacities[i] = (int *) malloc((totalLine+1) *sizeof(int));		//allocating array with size totalLine+1
		if(flows[i] == NULL || capacities[i] == NULL){	//If no enough memory
			fprintf(stderr, "out of memory %d\n",i);
			return;
		}
		else
			for(int j=0; j <= totalLine; j++){	//firstly assigning all elements to 0
				capacities[i][j] = 0;
				flows[i][j] = 0;
			}
	}

	int v1, v2, cap;
	ifstream read;
	read.open(inputName.c_str(), ios::in);
		if (read.fail()) {	//if the given input file can not be opened
		  cerr << "Could not open file ";
		  cerr << inputName;
		  cerr << ".\n";
		  return;
		}
		while(!read.eof()){
			read >> v1 >> v2 >> cap;
			capacities[v1][v2] = cap;	//capacity of v1-v2 agencies assigning necessary plot in arrays
			flows[v1][v2] = cap;
		} 
	lastNodeNum = v2;	//lastNodeNum(class private member) is assigned sink node
	read.close();
}

void Agency::readFlows(string inputName) {
	/************************************************************************************
	*	Function Name	  : readFlows													*
	*	Aim to be written : reading the given input file to the class parameter 'flows'	*
	*								(will be used before each Mission 2 calling			*
	*	Parameters		  : string parameter of input file name							*
	*	Return value      : ---															*
	*************************************************************************************/
	for(int i=0; i <= lastNodeNum; i++){	
		for(int j=0; j <= lastNodeNum; j++){
			flows[i][j] = capacities[i][j];		//filling flows to real capacities
		}
	}
	int v1, v2, val;
	ifstream read;
	read.open((inputName).c_str(), ios::in);
		if (read.fail()) {	//if the given input file can not be opened
		  cerr << "Could not open file ";
		  cerr << inputName;
		  cerr << ".\n";
		  return;
		}
		while(!read.eof()){
			read >> v1 >> v2 >> val;
			flows[v1][v2] = capacities[v1][v2] - val;	//If given input used the v1-v2 capacity then minus it from cap..
			flows[v2][v1] = val;	//for residual graph	
		} 
	read.close();
}

void Agency::readFlowsBeginning(string inputName) {
	/************************************************************************************
	*	Function Name	  : readFlows													*
	*	Aim to be written : reading the given input file to the class parameter 'flows'	*
	*								(will be used before each Mission 1 calling			*
	*	Parameters		  : string parameter of input file name							*
	*	Return value      : ---															*
	*************************************************************************************/
	for(int i=0; i <= lastNodeNum; i++){
		for(int j=0; j <= lastNodeNum; j++){
			flows[i][j] = 0;					//firstly, there is no flow
		}
	}
	int v1, v2, val;
	ifstream read;
	read.open(inputName.c_str(), ios::in);
		if (read.fail()) {	//if the given input file can not be opened
		  cerr << "Could not open file ";
		  cerr << inputName;
		  cerr << ".\n";
		  return;
		}
		while(!read.eof()){		
			read >> v1 >> v2 >> val;
			flows[v1][v2] = val;		//fill the all flows according to given input file
		} 
	read.close();
}

bool Agency::BFS(int s, int t) {
	/************************************************************************************
	*	Function Name	  : BFS															*
	*	Aim to be written : searching a path between s and t agencies, if there is then	*
	*								returning true... else false						*
	*	Parameters		  : integer to starting agency number, and other to end			*
	*	Return value      : boolean variable (if found a path, true)					*
	*************************************************************************************/
   queue<int> LAYER;	//queue for BFS
   bool found = false;
   int currentElement;
   assignAll(nodeBeforeMe, -1, lastNodeNum);	//firstly, make all before's -1. That will be used to determine path agencies
   LAYER.push(s);
   nodeBeforeMe[s] = s;
   
   while( !LAYER.empty() && !found) {	//while not found and queue is not empty
	  currentElement = LAYER.front();	//getting first element of queue
	  LAYER.pop();	//pop from the queue
      for(int i=1; i<=lastNodeNum; i++) {	//for all possible agencies
         if(flows[currentElement][i] != 0 && nodeBeforeMe[i] == -1) {	//if there is a flow different from 0 
			LAYER.push(i);												//and the agency is not expired before
			nodeBeforeMe[i] = currentElement;  
			 if(i == t) {
               found = true;
               break;
             }
         }
      }
   }
   return found;
}

void Agency::findMaxFlow(int mission){
	/****************************************************************************************************
	*	Function Name	  : findMaxFlow																	*
	*	Aim to be written : searching maximum flow with trying all possible paths from source to sink	*
	*	Parameters		  : integer to determining Mission 1 or 2										*
	*	Return value      : boolean variable (if found a path, true)									*
	****************************************************************************************************/
   int temp, minumumCapacity;
   bool isMaxCap = true;
   if(mission == 1)
		cout << "\nTraces and capacities(from sink to source):\n\n\t";
   else if(mission == 2)
		cout << "\nPossible trace(from sink to source):\n\n\t";
   while(BFS(1, lastNodeNum)) {		//while there is a possible 1-lastNodeNum(s-t) path
       minumumCapacity = flows[nodeBeforeMe[lastNodeNum]][lastNodeNum];
       temp = lastNodeNum;
       while(nodeBeforeMe[temp] != temp) {		//while for determining minumum capacity of the found path
		  isMaxCap = false;
		  cout << temp << "-";
          if(flows[nodeBeforeMe[temp]][temp] < minumumCapacity)
             minumumCapacity = flows[nodeBeforeMe[temp]][temp];
          temp = nodeBeforeMe[temp];
       }
	   cout << temp;
       
       temp = lastNodeNum;		//From here to next 5lines have similar tasks as the Augment function in our presentation
       while(nodeBeforeMe[temp] != temp) {		//while for subtraction to used capacity to the all agencies on the found path
          flows[nodeBeforeMe[temp]][temp] -= minumumCapacity;	//We've already gone here, so that delete our cost
          flows[temp][nodeBeforeMe[temp]] += minumumCapacity;	//For residual graph
          temp = nodeBeforeMe[temp];
       }
	   cout << " " << minumumCapacity << "\n\n\t";
       totalFlow += minumumCapacity;
   }
   if(isMaxCap)	//For Mission 2
	   cout << "\nNo possible traces. Therefore it is maximum flow. \n";
   else
	   cout << "\nThe max flow from s to t is : " << totalFlow << "\n\n"; 
   totalFlow = 0;
}

void Agency::assignAll(int *arrayWillBeChanged, int newValue, int endOfArray){
	/********************************************************************************************
	*	Function Name	  : assignAll															*
	*	Aim to be written : assigning from beginning to end(endOfArray) element of given array	*
	*								to a given new value 							 			*
	*	Parameters		  : array that values will be changed, new value of array elements		*
	*								end index of array											*
	*	Return value      : ---																	*
	*********************************************************************************************/
	for(int i=0; i<=endOfArray; i++)
		arrayWillBeChanged[i] = newValue;
}

int Agency::getTotalFlow(){
	return totalFlow;
}

#endif