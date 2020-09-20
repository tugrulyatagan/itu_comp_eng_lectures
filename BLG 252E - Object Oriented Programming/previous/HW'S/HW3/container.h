/*
*
* BLG252E
* 2011 Spring
* 3rd Homework
*
*
*
*
* Student Name: ABDULLAH AYDEÐER
* Student ID : 040090533
*
*
*/
#ifndef CONTAINER_H           
#define	CONTAINER_H
#include <iostream>
using namespace std;

template <class Type>
	class Container{
		private:
			Type *dizi;					//This is generic array
			int numberOfElements;		//This holds the number of elements of generic array
		public:
			Container(){
				dizi = new Type[200];	//Default constructor allocates 20 member for generic array
				numberOfElements = 0;}	

			Container(int number){
				dizi = new Type[5*number];	//Constructor allocates 2*number member for generic array
				numberOfElements = 0;}

			void addToArray(Type addType){
				dizi[addType.getID()] = addType;	//In this line, adding the new member to generic array according to new member id
				numberOfElements++;}		//Incrementing the number of elements of generic array

			Type Container<Type>::takeFromArray(int number){
				Type t = dizi[0];
				if(number>6 || number<0){		//If passing integer is not valid
					cout<<"WRONG NUMBER\n";		//Then cout wrong number and
					return t;}					//return the first element of generic array
						t = dizi[number];
						Person p = Person();
						dizi[number] = p;	//For taking array, adding new Person to this partition
						numberOfElements--;		//Decreasing the number of elemets of generic array
				return t;}

			Type getArray(int number){		//This function get one element from generic array according to integer parameter
				Type t = dizi[0];
				if(number>6 ||number<0){
					cout<<"WRONG NUMBER\n";
					return t;}
				return dizi[number];}

			int getnumberOfElements() const{
				return numberOfElements;}
	};

#endif