#include "Traversal.h"
#include <string>
//Reset the buffers. Simply put "" characters to indicate the buffer doesn't contain any valid value
void Traversal::flush(){

	visitedIndex=0;
	toBvisitedIndex=0;
	
	for(int i=0;i<bufferCap;i++){
		visited[i]="";
		toBvisited[i]="";
	}
}

//Check a buffer<par1> if it contains a value<par2>
bool Traversal::contains(string* dizi,string s){
	for(int i=0;i<bufferCap;i++)
		if(dizi[i]==s)
			return true;
	return false;        
};

//Claim memory for buffers and reset them.
Traversal::Traversal(){   
	bufferCap=100; 
	visited=new string[bufferCap];
	toBvisited=new string[bufferCap];
	flush();
}
