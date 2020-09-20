
/************************************************************************************************
* About the writer;																				*
* Student Name: Abdullah AYDEGER																*
* Student Number: 040090533																		*
*************************************************************************************************
* About the code;																				*
* File Name: NodeData.h																			*
* Reason Of Writing: Holding each word in the sonnets with the real data and the				*
*						 string value which determines where the string place in.				*
*************************************************************************************************/


#ifndef _NODEDATA_H_
#define _NODEDATA_H_


#include <iostream>
#include <iomanip>
#include <string>
#include <list>

#define SIZE 50	//Supposing the same word can be found in maximum 50times

using namespace std;

class NodeData{
	public:
		string data;			//words in the sonnets
		string places[SIZE];	//places with coordinates with string array(example:(4,6) )
		int slot;				//holding how many times the same word is seen

		NodeData(){				//Default constructor
		slot = 0;				
		for(int i=0; i<SIZE; i++)
			places[i].clear();		//All places is clearing
		};

		NodeData(string d, string p){	//Constructor for NodeData class with necessary parameters
			slot = 0;
			data = d;
			for(int i=0; i<SIZE; i++)
				places[i].clear();
			places[slot] = p; 
			slot++;
		}

		void insertData(string p){
			/*
			* This function is used for adding new place to places array
			*/
			places[slot] = p;
			slot++;
		}

		void assign(NodeData nd){
			/*
			* This function is used for assigning one NodeData to other
			*/
			int i = 0;
			data = nd.data;
			slot = nd.slot;
			for(; !nd.places[i].empty(); i++){
				places[i] = nd.places[i];
				nd.places[i].clear();
			}
			for(; i < SIZE; i++)
				places[i].clear();
			nd.slot = 0;
		}

		void create(string s, string p){
			slot = 0;
			data = s;
			for(int i=0; i<SIZE; i++)
				places[i].clear();
			places[slot] = p; 
			slot++;
		}

};


#endif