/********************************************************************************
*	Name Surname: Aykut Akin													*
*	Number		: 040080177														*
*	Due Date	: 23.03.2011													*
*																				*
*	Every information about functions and classes can be found in report		*
*																				*
*********************************************************************************/

#include <ctime>
#include "MWP_Gale_Shapley.h"

using namespace std;

int main(int argc, char* argv[]) 
{     
	string command;
	Heap* men=NULL;
	Heap* women=NULL;
    clock_t start_clk, end_clk; 
	/*
	argc=6;
	argv[0]="GS";
	argv[1]="-i";
	argv[2]="ppm_100.txt";	
	argv[3]="ppw_100.txt";
	argv[4]="-o";
	argv[5]="GS_100_out.txt";
	*/
		if(argc==6){
			if(command.assign("./GS").compare(argv[0])==0 && 
				command.assign("-i").compare(argv[1])==0 &&
				command.assign("-o").compare(argv[4])==0){
				
					men = new Heap(argv[0],argv[2]);
					women = new Heap(argv[0],argv[3]);
					start_clk = clock();
					gale_shapley(*men,*women);
					end_clk = clock(); 
					men->writeData(argv[5],(end_clk-start_clk)*100/CLOCKS_PER_SEC);
			}
		}
		if(men!=NULL && women!=NULL){
			delete men;
			delete women;
		}
   return 0; 
}