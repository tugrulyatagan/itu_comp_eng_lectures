/************************************************************
*	Name Surname		: Abdullah AYDEÐER					*
*   Number				: 040090533							*
*	University			: Istanbul Technical University		*
*	Lecture				: Computer Communications			*
*	Lecturer			: Sema OKTUG						*
*	Project Number		: 2									*
*	Created Date		: 29.12.2012						*
*	Purpose of class	: Inherited from Pair and hiding 3	*
*							integer variable into one struct*
*************************************************************/

#ifndef TRIPLE_H
#define TRIPLE_H	

#include "Pair.h"

class Triple : public Pair{
	public:
		int cost;	
};

#endif

