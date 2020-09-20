/********************************************************************************
*	Name Surname: Aykut Akin													*
*	Number		: 040080177														*
*	Due Date	: 23.03.2011													*
*																				*
*	Every information about functions and classes can be found in report		*
*																				*
*********************************************************************************/

#include <ctime>
#include "graph.h"

using namespace std;

int main(int argc, char* argv[]) 
{     
	clock_t start_clk, end_clk; 

	Graph graph("cityplan.txt");
	start_clk = clock();
	for(int i=0; i<1000; i++){
		graph.kruskal();
		if(i!=999)
			graph.clear();
	}
	end_clk = clock(); 
	graph.writeData((end_clk-start_clk)*100/CLOCKS_PER_SEC);

   return 0;
}