/********************************************************************************
*	Name Surname: Aykut Akin													*
*	Number		: 040080177														*
*	Due Date	: 09.05.2011													*
*																				*
*	Every information about functions and classes can be found in report		*
*																				*
*********************************************************************************/

#include "towers.h"

int main(){

	Towers tower("babylon.txt");
	tower.setGraphWithTopOrder();
	tower.getAnswers();
	getchar();

    return 0;
}