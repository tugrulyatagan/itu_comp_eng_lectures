/************************************************************
*	Name Surname		: Abdullah AYDEÐER					*
*   Number				: 040090533							*
*	University			: Istanbul Technical University		*
*	Lecture				: Computer Communications			*
*	Lecturer			: Sema OKTUG						*
*	Project Number		: 2									*
*	Created Date		: 29.12.2012						*
*	Purpose of class	: Keeping link recovery informations*
*************************************************************/

#ifndef RECOVERY_H
#define RECOVERY_H	

class Recovery{
	public:
		double timeToRecover;	//time needs for current recovery
		int numberOfFailure;	//current recovery's failure (which failure will be solved with this)
};

#endif

