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
	argv[0]="GSW";
	argv[1]="-i";
	argv[2]="ppm_10.txt";	
	argv[3]="ppw_10.txt";
	argv[4]="-o";
	argv[5]="GSW_10_out.txt";
	*/
		if(argc==6){
			if(command.assign("./GSW").compare(argv[0])==0 && 
				command.assign("-i").compare(argv[1])==0 &&
				command.assign("-o").compare(argv[4])==0){
				
					men = new Heap(argv[0],argv[2]);
					women = new Heap(argv[0],argv[3]);
					start_clk = clock();
					w_gale_shapley(*women,*men);
					end_clk = clock(); 
					women->writeData(argv[5],(end_clk-start_clk)*100/CLOCKS_PER_SEC);
			}
		}
		if(men!=NULL && women!=NULL){
			delete men;
			delete women;
		}
   return 0; 
} 