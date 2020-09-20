/********************************************************************************
*	Name Surname: Aykut Akin													*
*	Number		: 040080177														*
*	Due Date	: 23.03.2011													*
*																				*
*	Every information about functions and classes can be found in report		*
*																				*
*********************************************************************************/

#include "MWP_Gale_Shapley.h"
#include <time.h>

void gale_shapley(Heap& men, Heap& women){

	int number = men.getHeapSize();
	srand ( time(NULL) );
	while(is_free_person(men)){
		int i = rand() % number + 1;		
		if(men.engagements[i] == 0){
			bool free = true;
			while(free && men.count[i] < number){
				men.count[i]++;
				int woman = *men.roots[i];
				men.roots[i]++;

				if(women.engagements[woman]==0){
					men.engagements[i] = woman;
					women.engagements[woman] = i;
					free = false;
				}

				else if(women.inverse[woman][women.engagements[woman]] > women.inverse[woman][i]){
					men.engagements[women.engagements[woman]] = 0;
					men.engagements[i] = woman;
					women.engagements[woman] = i;	
					free = false;
				}
			}
		}
	}
}

void w_gale_shapley(Heap& women, Heap& men){

	int number = men.getHeapSize();
	srand ( time(NULL) );
	while(is_free_person(women)){
		int i = rand() % number + 1;
		if(women.engagements[i] == 0){
			bool free = true;
			while(free && women.count[i] < number){
				women.count[i]++;
				int man = *women.roots[i];
				women.roots[i]++;

				if(men.engagements[man]==0){
					women.engagements[i] = man;
					men.engagements[man] = i;
					free = false;
				}

				else if(men.inverse[man][men.engagements[man]] > men.inverse[man][i]){
					women.engagements[men.engagements[man]] = 0;
					women.engagements[i] = man;
					men.engagements[man] = i;	
					free = false;
				}
			}
		}
	}
}

void p_gale_shapley(Heap& men, Heap& women){
	
	int number = men.getHeapSize();
	bool stop=false;
	srand ( time(NULL) );
	while(!stop){
		int i = rand() % number + 1;
		if(men.engagements[i] == 0){
			if(men.wealth[i] !=0 ){
				bool free = true;
				while(free && men.count[i] < number){
					men.count[i]++;
					int woman = *men.roots[i];
					men.roots[i]++;

					if(women.engagements[woman]==0){
						men.engagements[i] = woman;
						women.engagements[woman] = i;
						men.wealth[i]--;
						free = false;
					}
				
					else if(women.inverse[woman][women.engagements[woman]] > women.inverse[woman][i]){
						if(women.wealth[woman] !=0 ){
							men.engagements[women.engagements[woman]] = 0;
							men.engagements[i] = woman;
							women.engagements[woman] = i;
							women.wealth[woman]--;
							free = false;
						}
					}
				}
			}
		}
		else{
			for(int j=1; j<=number; j++){
				if(men.engagements[j]==0 && men.wealth[j]!=0)
					break;
				if(j==men.getHeapSize())
					stop = true;
			}
		}
	}
}

bool is_free_person(Heap& person){
	
	bool free = false;
	int number = person.getHeapSize();
	for(int i=1; i<=number; i++){
		if(person.engagements[i] == 0){
			free = true;
			break;
		}
	}
	return free;			
}
