#include<stdio.h>
#include<pthread.h>
#include<time.h>

pthread_mutex_t lock_1,lock_2;

void* faulty_functionA(void *arg){
 
   	pthread_mutex_lock(&lock_1);           
	printf("\nA kritik bölge 1'de\n");
	fflush(stdout);

	sleep(2);
   	pthread_mutex_lock(&lock_2);          
 
	printf("\nA kritik bölge 2'de\n");
	fflush(stdout);

   	pthread_mutex_unlock(&lock_2);
   	pthread_mutex_unlock(&lock_1);
}

void* faulty_functionB(void *arg){
	sleep(1);
   	pthread_mutex_lock(&lock_2);           
	printf("\nB kritik bölge 2'de\n");
	fflush(stdout);

	sleep(2);
   	pthread_mutex_lock(&lock_1);           
 
	printf("\nB kritik bölge 1'de\n");
	fflush(stdout);

   	pthread_mutex_unlock(&lock_1);
   	pthread_mutex_unlock(&lock_2);

}

void* functionA(void *arg){
 
   	pthread_mutex_lock(&lock_1);           
	printf("\nA kritik bölge 1'de\n");
	fflush(stdout);
	
	sleep(5);
	while(pthread_mutex_trylock(&lock_2)){
	   	pthread_mutex_unlock(&lock_1);
		sleep(1);	
		printf("\nA bekliyor\n");
		fflush(stdout);
  		pthread_mutex_lock(&lock_1);           
	}
 
	printf("\nA kritik bölge 2'de\n");
	fflush(stdout);

   	pthread_mutex_unlock(&lock_2);
   	pthread_mutex_unlock(&lock_1);
}

void* functionB(void *arg){
	sleep(1);
   	pthread_mutex_lock(&lock_2);           
	printf("\nB kritik bölge 2'de\n");
	fflush(stdout);

	sleep(4);
   	while(pthread_mutex_trylock(&lock_1)){
	   	pthread_mutex_unlock(&lock_2);
		sleep(1);	
		printf("\nB bekliyor\n");
		fflush(stdout);
  		pthread_mutex_lock(&lock_2);           
	}           
 
	printf("\nB kritik bölge 1'de\n");
	fflush(stdout);

   	pthread_mutex_unlock(&lock_1);
   	pthread_mutex_unlock(&lock_2);

}

int main(){

	pthread_t threadA,threadB;
	

	pthread_mutex_init(&lock_1,NULL);
	pthread_mutex_init(&lock_2,NULL);

	//if( pthread_create(&threadA,NULL,functionA,NULL)){	
	if( pthread_create(&threadA,NULL,faulty_functionA,NULL)){
		printf("error creating thread");
		exit(1);
	}
	//if( pthread_create(&threadA,NULL,functionB,NULL)){	
	if( pthread_create(&threadB,NULL,faulty_functionB,NULL)){
		printf("error creating thread");
		exit(1);
	}

	if( pthread_join(threadA,NULL)){
		printf("error joining thread");
		exit(1);
	}
	if( pthread_join(threadB,NULL)){
		printf("error joining thread");
		exit(1);
	}

	pthread_mutex_destroy(&lock_1);
	pthread_mutex_destroy(&lock_2);

	return 0;
}