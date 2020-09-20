/********************************************************************************
*	Name Surname: Aykut Akin													*
*	Number		: 040080177														*
*	Due Date	: 23.03.2011													*
*																				*
*	Every information about functions and classes can be found in report		*
*																				*
*********************************************************************************/

#ifndef __GALE_H__
#define __GALE_H__

#include "Heap.h"
#include <vector>

	void gale_shapley(Heap&, Heap&);
	void w_gale_shapley(Heap &, Heap &);
	void p_gale_shapley(Heap &, Heap &);
	bool is_free_person(Heap&);
	void randomNumberVector(int);

#endif