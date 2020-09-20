#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Pair.h"

using namespace std;

//Comment all locks for race condition
bool Pair::operator<( Pair &other){

	this->lock();
	//sleep(1); 	//Uncomment to ensure deadlock
	other.lock();

	if(this->a<other.a){
		this->unlock();
		other.unlock();
		return true;
	}

	if(this->a==other.a && this->b<other.b){
		this->unlock();
		other.unlock();
		return true;
	}


	this->unlock();
	other.unlock();

	return false;
}

bool Pair::operator>( Pair &other){
	this->lock();
	//sleep(1);		//Uncomment to ensure deadlock
	other.lock();

	if(this->a>other.a){
		this->unlock();
		other.unlock();
		return true;
	}

	if(this->a==other.a && this->b>other.b){
		this->unlock();
		other.unlock();
		return true;
	}

	this->unlock();
	other.unlock();

	return false;
}

bool Pair::operator==( Pair &other){
	this->lock();
	//sleep(1);		//Uncomment to ensure deadlock
	other.lock();

	if(this->a==other.a && this->b==other.b){
		this->unlock();
		other.unlock();
		return true;
	}

	this->unlock();
	other.unlock();

	return false;
}

Pair::Pair(int a,int b){
	this->a=a;
	this->b=b;
	pthread_mutex_init(&plock,NULL);
}

Pair::Pair(){
	this->a=(rand()%10);
	this->b=(rand()%10);
	pthread_mutex_init(&plock,NULL);
}

Pair::~Pair(){
	pthread_mutex_destroy(&plock);
}

void Pair::print(string name){
	cout << endl << name << ": (" << this->a <<","<<this->b<<")"<<endl;
}

void Pair::setA(int a){
	this->lock();
	this->a=a;
	this->unlock();
}

void Pair::setB(int b){
	this->lock();
	this->b=b;
	this->unlock();
}

void Pair::setAB(int a,int b){
	this->lock();
	this->a=a;
	this->b=b;
	this->unlock();
}

void Pair::lock(){
	pthread_mutex_lock(&plock);
}

void Pair::unlock(){
	pthread_mutex_unlock(&plock);
}
