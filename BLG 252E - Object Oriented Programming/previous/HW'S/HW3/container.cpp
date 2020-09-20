/* I can not understand why this container.cpp works properly.
 Therefore, I need to comment this and write all necessary 
 functions in header file with less effective way...*/

/*#include "container.h"

template <class Type>
Container<Type>::Container(){
	dizi = new Type[8];
	size = 8;
	numberOfElements = 0;
};

template <class Type>
Container<Type>::Container(int number){
	size = number;
	dizi = new Type[size];
	numberOfElements = 0;
}

template <class Type>
void Container<Type>::addToArray(Type addType){
	dizi[numberOfElements++] = addType;
}

template <class Type>
Type Container<Type>::takeFromArray(int number){
	Type t = dizi[i];
	for(int i=number; i<size; i++)
		dizi[i] = dizi[i+1];
	numberOfElemets--;
	return t;
}

template <class Type>
Type Container<Type>::getArray(int number){
	return dizi[number];
}

/*template <class Type>
Type* Container<Type>::getArray(){
	return *dizi;
}

template <class Type>
int Container<Type>::getSize() const{
	return size;
}

template <class Type>
int Container<Type>::getnumberOfElements() const{
	return numberOfElements;
}*/