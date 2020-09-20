#include "Agency.h"

int menu_print();
using namespace std;

int main(int argc, char *argval[],char *env[]){
	if(argc != 3){	//if any of parameters does not entered by using terminal
		cout<<"Wrong running command";
		return 0;
	}

	string inputName1 = argval[1];
	string inputName2 = argval[2];
	Agency A(inputName1);
	int c = menu_print();
	 while(c != 3){
		 switch (c){
		 case 1:
			 cout << "\n***** MISSION 1 *****\n";
			 A.readFlowsBeginning(inputName1);
			 A.findMaxFlow(1);
			 getchar();
			 getchar();
			 c = menu_print();
			 break;
		 case 2:
			 cout << "\n***** MISSION 2 *****\n";
			 cout << "\nIs maximum flow?\n";
			 A.readFlows(inputName2);
			 A.findMaxFlow(2);
			 getchar();
			 getchar();
			 c = menu_print();
			 break;
		 case 3:
			 exit(0);
		 }
	 }
}


int menu_print(){
	/************************************************************************************
	*	Function Name	  : menu_print													*
	*	Aim to be written : showing the list of choices that user can be choose 		*
	*	Parameters		  : --															*
	*	Return value      : integer that showing the choice								*
	*************************************************************************************/
	int choice;
	//system("cls");     //For windows (cleaning the screen)
	system("clear");	//For Linux
	cout <<"1. Mission-1 \n"
		   "2. Mission-2 \n"
		   "3. Exit\n";
	cout << "Your choice:";
	cin>>choice;
	return choice;	//assuming the user will enter integer, otherwise the program will run in infinity loop
}