#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Pair.h"

using namespace std;

void* thread_function(void *arg){

	Pair** pList=(Pair**) arg;
	

	pList[0]->print("x");
	pList[1]->print("y");
		
	sleep(2);

	if((*pList[0])>(*pList[1]))
		cout<<endl<<"x>y"<<endl;
	
	if((*pList[0])<(*pList[1]))
		cout<<endl<<"x<y"<<endl;

	if((*pList[0])==(*pList[1]))
		cout<<endl<<"x=y"<<endl;


	return NULL;
}

int main(){

	pthread_t mythreadA,mythreadB;

	srand(time(NULL));

	Pair* x=new Pair(1,2);
	Pair* y=new Pair(2,3);

	Pair* pList[]={x,y};
	//Pair* qList[]={y,x};	//Uncomment for deadlock

	if( pthread_create(&mythreadA,NULL,thread_function,(void*) pList)){
		printf("error creating thread");
		abort();
	}
/*	//Uncomment for deadlock
	if( pthread_create(&mythreadB,NULL,thread_function,(void*) qList)){	
		printf("error creating thread");				
		abort();							
	}									
*/


//Uncomment for a race condition
/*
	sleep(1);

	x->setA(5);
	pList[0]->print("x");
*/

	if( pthread_join(mythreadA,NULL)){
		printf("error joining thread");
		abort();
	}
/*   //Uncomment for deadlock
	if( pthread_join(mythreadB,NULL)){			
		printf("error joining thread");			
		abort();					
	}							
*/
	return 0;
}
