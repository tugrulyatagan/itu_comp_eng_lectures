/*
* @Author
* Student Name: Tuðrul YATAÐAN
* Student ID : 040100117
* Date: 19.05.2013
*/

#ifndef ARITHMETICVECTOR_H
#define ARITHMETICVECTOR_H
#include <vector>
#include <string>
using namespace std;

template <class MyType> // template class
class ArithmeticVector{
	private:
		vector<MyType> AV; // data vector 
		int size;
	public:
		ArithmeticVector<MyType>(int); // constructor takes size info
		void print()const; // print method
		bool contains(MyType)const; // checks if valu is in vector
		ArithmeticVector<MyType> operator+(const ArithmeticVector<MyType> &)const; // + operator
		ArithmeticVector<MyType> operator/(const ArithmeticVector<MyType> &)const; // / operator
		void operator=(const ArithmeticVector<MyType> &); // assign operator
		bool operator==(const ArithmeticVector<MyType> &)const; // == operator
		MyType & operator[](int); // [] operator can be used right and left side operation
		void operator++(); // increment operator
		void operator--(); // decrement operator
};


template <class MyType>
ArithmeticVector<MyType>::ArithmeticVector(int s):size(s){
	for (int n=0; n<size; n++) 
		AV.push_back(rand() % 10); // add random number to end of vector
}

template <class MyType>
void ArithmeticVector<MyType>::print()const{
	for (int n=0; n<size; n++) 
		cout << AV[n] << " ";
	cout << endl;
}

template <class MyType>
bool ArithmeticVector<MyType>::contains(MyType N)const{
	for(int i=0; i < size; i++)
		if(AV[i] == N) return 1; // if value is found return TRUE
	return 0; // value is not found return FALSE
}

template <class MyType>
ArithmeticVector<MyType> ArithmeticVector<MyType>::operator+(const ArithmeticVector<MyType> &in)const{
	if (size != in.size) throw string("Sizes are not equal"); // if sizes are not equal throw exception
	ArithmeticVector<MyType> result(size); // create result arithmetic vector
	for(int i=0; i < size; i++)
		result[i] = AV[i] + in.AV[i]; // sum elements by one by
	return result;
}

template <class MyType>
ArithmeticVector<MyType> ArithmeticVector<MyType>::operator/(const ArithmeticVector<MyType> &in)const{
	if (size != in.size) throw string("Sizes are not equal"); // if sizes are not equal throw exception
	ArithmeticVector<MyType> result(size); // create result arithmetic vector
	for(int i=0; i < size; i++)
		result[i] = AV[i] / in.AV[i]; // divide elements by one by
	return result;
}

template <class MyType>
void ArithmeticVector<MyType>::operator=(const ArithmeticVector<MyType> &in){
	if (size != in.size) throw string("Sizes are not equal"); // if sizes are not equal throw exception
	AV=in.AV; // assign right side to left side
}

template <class MyType>
bool ArithmeticVector<MyType>::operator==(const ArithmeticVector<MyType> &in)const{
	if (size != in.size) throw string("Sizes are not equal"); // if sizes are not equal throw exception
	for(int i=0; i < size; i++)
		if(AV[i] != in.AV[i]) return 0;  // if one value is different return FALSE
	return 1; // vectors are same return TRUE
}

template <class MyType>
MyType & ArithmeticVector<MyType>::operator[](int i){
	if (i >= size) throw string("Index out of bounds"); // if index is too large throw exception 
	return AV[i]; // return value in that index
}

template <class MyType>
void ArithmeticVector<MyType>::operator++(){
	for(int i=0; i < size; i++)
		++AV[i]; // increment elements by one by
}

template <class MyType>
void ArithmeticVector<MyType>::operator--(){
	for(int i=0; i < size; i++)
		--AV[i]; // decrement elements by one by
}

#endif
