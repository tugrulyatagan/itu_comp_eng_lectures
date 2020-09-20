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
	argc=9;
	argv[0]="GSP";
	argv[1]="-i";
	argv[2]="ppm_5.txt";	
	argv[3]="ppw_5.txt";
	argv[4]="-w5";
	argv[5]="mw_5.txt";	
	argv[6]="ww_5.txt";
	argv[7]="-o";
	argv[8]="GSP_5_out.txt";
	*/
		if(argc==9){
			if(command.assign("./GSP").compare(argv[0]) ==0 && 
				command.assign("-i").compare(argv[1])==0 &&
				command.assign("-o").compare(argv[7])==0 &&
				command.assign("-w").compare(0,2,argv[4],0,2)==0){
				
					men = new Heap(argv[0],argv[2],argv[5],argv[4]);
					women = new Heap(argv[0],argv[3],argv[6],argv[4]);
					start_clk = clock();
					p_gale_shapley(*men, *women);
					end_clk = clock(); 
					men->writeData(argv[8],(end_clk-start_clk)*100/CLOCKS_PER_SEC);
			}
		}
		if(men!=NULL && women!=NULL){
			delete men;
			delete women;
		}
   return 0; 
} 