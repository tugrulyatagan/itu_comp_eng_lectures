#include "CompNode.h"

using namespace std;

int menu_print();	
void listAllInfected(list<CompNode *>, int, int);
void isInfected(list<CompNode *>, int, int, int);

int main(int argc, char *argval[],char *env[]){
	if(argc != 4){	//if any of parameters does not entered by using terminal
		cout<<"Wrong running command";
		return 0;
	}
	
	char *inputName = argval[1];	//second parameter is input file's name
	//string inputName = "a.txt";
	ifstream read;	//using for file operations
	int num1, num2, time;
	int v_time, v_num;
	v_num = atoi(argval[2]);	//converting the given char* parameter to integer
	//v_num = 1; v_time = 1;
	v_time = atoi(argval[3]);	//converting the given char* parameter to integer
	CompNode *cp12, *cp21;
	list<CompNode*> cp11, cp22;	
	list<CompNode*> ALL;	//List for all computer nodes -> This can cause very huge memory spent
	read.open(inputName, ios::in);
		if (read.fail()) {	//if the given input file can not be opened
		  cerr << "Could not open file ";
		  cerr << inputName;
		  cerr << ".\n";
		  return 1;
		  }

		while(!read.eof()){
			read >> num1 >> num2 >>  time;

			cp21 = new CompNode(num1, time);
			cp11 = CompNode::isExist(ALL, num1);

			if( !cp11.empty())
				CompNode::addNeighbour(cp11, cp21);		
			CompNode::addToALL(&ALL, cp21);
 
			
			cp22 = CompNode::isExist(ALL, num2);
			cp12 = new CompNode(num2, time);

			if( !cp22.empty() )
				CompNode::addNeighbour(cp22, cp12);
			CompNode::addToALL(&ALL, cp12);
				
			CompNode::makeTheyConnected(cp21, cp12);
			
		} 
	read.close();
	CompNode::virusInfected(v_num, v_time, &ALL);
	int i = 0;
	int no;
	 int c = -1;
	 c = menu_print();
	 while(c != 3){
		 switch (c){
		 case 1:
			 listAllInfected(ALL, v_num, v_time);
			 getchar();
			 getchar();
			 c = menu_print();
			 break;
		 case 2:
			 cout << "Please enter the no of computer: \n"; 
			 cin >> no;
			 isInfected(ALL, no, v_num, v_time);
			 getchar();
			 getchar();
			 c = menu_print();
			 break;
		 case 3:
			 exit(0);
			 break;
		 default:
			 cout << "\nWrong enter, please enter your choice again\n";
			 getchar();
			 getchar();
			 c = menu_print();
			 break;
		 }
	 }
return 0;
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
	cout <<"1. List the computers which can be infected?\n"
		   "2. Enter a computer no in order to test if it is infected?\n"
		   "3. Exit\n"
		   "Your choice(must be an integer):";
	cin>>choice;
	return choice;	//assuming the user will enter integer, otherwise the program will run in infinity loop
}

void listAllInfected(list<CompNode *> ALL, int vNum, int vTime){
	/************************************************************************************************************************
	*	Function Name	  : listAllInfected																					*
	*	Aim to be written : showing the all of infected nodes' num and time to be infected first in the screen an be choose *
	*	Parameters		  : --																								*
	*	Return value      : integer that showing the choice																	*
	*************************************************************************************************************************/
	list<CompNode *>::iterator it, it2;
	list<CompNode *> infected;	//using for holding the list of infected computer pointers
	cout << "Computers can be infected by the trace (computer_no timestamp):\n";
	cout << " First virus, num: " << vNum << " time: " << vTime <<endl;
	for(it2 = ALL.begin(); it2 != ALL.end(); it2++){	//for all nodes
		if((*it2)->getInfected() == true)	//if the current node is infected
			if( (*it2)->getNum() != vNum)	//if the current node is not the first node that virus has been infected
				infected.insert(infected.begin(), *it2);	//add to the infected list
	}
	if( !infected.empty() ){
		for(it2 = infected.begin(); it2 != infected.end(); it2++){	
				//this loop for removing the nodes with same num value in the infected list
			if(!(*it2)->neighbour.empty())
				for(it = (*it2)->neighbour.begin(); it != (*it2)->neighbour.end(); it++){	
							//only smallest time with same num will exist in the list
					infected.remove((*it));
				}
		}
	}
	if( !infected.empty() ){
		cout << " NUM \t  TIME \n";		
		cout << "-----    ------ \n";
		for(it2 = infected.end(); it2 != infected.begin(); it2--)		//for all infected nodes, write the node num and time parameters in the screen
												//Need to start from end since output will become ascending order in the screen	
			if( it2 != infected.end() )		//end of list is absurd
				cout << "   " << (*it2)->getNum() << "  \t    " <<(*it2)->getTime() << endl;
	
		cout << "   " << (*infected.begin())->getNum() << "  \t    " <<(*infected.begin())->getTime() << endl;	//write first infected in the screen too
	}
	else
		cout << " There is no virus infected computer on the communication time \n";
}

void isInfected(list<CompNode *> ALL, int numberOfComp, int vNum, int vTime){
	/********************************************************************************************************************
	*	Function Name	  : isInfected																					*
	*	Aim to be written : determining the given node is infected or not, and if it is infected showing the			*
	*										path of virus from the first infected to the searching node					*	
	*	Parameters		  : list of all computer nodes(ALL), number of computer to be determining and first infected	*
	*															node num and time										*
	*	Return value      : --																							*
	*********************************************************************************************************************/
	if(numberOfComp == vNum){	//if given number for search is equal to the first computer's num that virus has been infected
		cout << numberOfComp << ". computer is the first infected computer in time " << vTime << endl;	
		return;
	}
	CompNode *it2;	//using for holding queue's popping elements
	list<CompNode *>::iterator it;
	CompNode *cp = new CompNode();
	list<CompNode *> effectPath;	//using for determining the path of virus between first infected node to the searching node
	cp = CompNode::getMyFirst(ALL, numberOfComp);	//determining first infected node with given numberOfComp
	if( !cp ){	//if given node has not been infected
		cout << numberOfComp << " has not been infected\n";
		return;
	}
	effectPath.insert(effectPath.begin(), cp);	//add first virused computer to the effected's list

	queue<CompNode *> effectedQ;	//one queue for travelling on the virus path
	effectedQ.push(cp);
	int tut = 0;	//special variable for to do not occur infinity loop
	while(!effectedQ.empty()){
		it2 = effectedQ.front();			
		effectedQ.pop();
		tut++;
		if(tut %2 == 1)
			for(it = it2->others.begin(); it != it2->others.end(); it++)
				(*it)->setTravelled(false);		//'travelled' variable for determining only 1 time the node will be travelled
	
		for(it = it2->others.begin(); it != it2->others.end(); it++){	//for all edges of current node
			if( (*it)->getInfected() == true && (*it)->getTravelled() == false ){
				(*it)->setTravelled(true);
				cp = CompNode::getMyFirst(ALL, (*it)->getNum());	//getting the first virus which number is equal to *its'
				effectedQ.push(cp);
				effectPath.insert(effectPath.begin(), cp);
				break;
			}
		}
	}
	for (it = ALL.begin(); it!=ALL.end(); it++)
		(*it)->setTravelled(true);	//make 'travelled' variable for all nodes true again for the isInfected function can be repeteable

	if(!effectPath.empty()){		//writing the path on the screen	
		cout<< "Trace virus\n";
		cout << " First virus, num: " << vNum << " time: " << vTime <<endl;
		for(it = effectPath.begin(); it!= effectPath.end(); it++)
			if( (*it)->getNum() != vNum)
				cout<< " Num: " << (*it)->getNum() << "  First time the node has been infected: " << (*it)->getTime() << endl;
	}
	else
		cout << numberOfComp << " has not been infected\n";		
}

		