/*
* @Author
* Student Name: Tugrul YATAGAN
* Student ID : 040100117
* Date: 19.05.2013
*/

#ifndef ARITHMETICVECTOR_H
#define ARITHMETICVECTOR_H
#include <vector>
#include <string>
using namespace std;

template <class MyType> // template class
class ArithmeticVector: public vector<MyType>{
	private:
		int size;
	public:
		ArithmeticVector<MyType>(int); // constructor takes size info
		void print() const; // print method
		bool contains(MyType)const; // checks if valu is in vector
		ArithmeticVector<MyType> operator+(const ArithmeticVector<MyType> &)const; // sum operator
		ArithmeticVector<MyType> operator/(const ArithmeticVector<MyType> &)const; // divide operator
		void operator=(const ArithmeticVector<MyType> &); // assign operator
		bool operator==(const ArithmeticVector<MyType> &)const; // compare operator
		MyType & operator[](int); // [] operator can be used right and left side operation
		void operator++(); // increment operator
		void operator--(); // decrement operator
};


template <class MyType>
ArithmeticVector<MyType>::ArithmeticVector(int s):size(s){
	for (int n=0; n<size; n++)
		this->push_back(rand() % 10); // add random number to end of vector
}

template <class MyType>
void ArithmeticVector<MyType>::print()const{
	for (int n=0; n<size; n++) 
		cout << this->at(n) << " "; // print elements by one by
	cout << endl;
}

template <class MyType>
bool ArithmeticVector<MyType>::contains(MyType N)const{
	for(int i=0; i < size; i++)
		if(this->at(i) == N) return 1; // if value is found return TRUE
	return 0; // value is not found return FALSE
}

template <class MyType>
ArithmeticVector<MyType> ArithmeticVector<MyType>::operator+(const ArithmeticVector<MyType> &in)const{
	if (size != in.size) throw string("Sizes are not equal"); // if sizes are not equal throw exception
	ArithmeticVector<MyType> result(size); // create result arithmetic vector
	for(int i=0; i < size; i++)
		result[i] = this->at(i) + in.at(i); // sum elements by one by
	return result;
}

template <class MyType>
ArithmeticVector<MyType> ArithmeticVector<MyType>::operator/(const ArithmeticVector<MyType> &in)const{
	if (size != in.size) throw string("Sizes are not equal"); // if sizes are not equal throw exception
	ArithmeticVector<MyType> result(size); // create result arithmetic vector
	for(int i=0; i < size; i++){
		if (in.at(i) == 0) throw string("Can not divide by 0"); // if divided by 0 throw exception
		result[i] = this->at(i) / in.at(i); // divide elements by one by
	}
	return result;
}

template <class MyType>
void ArithmeticVector<MyType>::operator=(const ArithmeticVector<MyType> &in){
	if (size != in.size) throw string("Sizes are not equal"); // if sizes are not equal throw exception
	for(int i = 0; i < size;i++)
		ArithmeticVector<MyType>::operator[](i) = in.at(i); // assign right side to left side elements by one by
}

template <class MyType>
bool ArithmeticVector<MyType>::operator==(const ArithmeticVector<MyType> &in)const{
	if (size != in.size) throw string("Sizes are not equal"); // if sizes are not equal throw exception
	for(int i=0; i < size; i++)
		if(this->at(i) != in.at(i)) return 0;  // if one value is different return FALSE
	return 1; // vectors are same return TRUE
}

template <class MyType>
MyType & ArithmeticVector<MyType>::operator[](int i){
	if (i >= size) throw string("Index out of bounds"); // if index is too large throw exception 
	return vector<MyType>::operator[](i); // return value in that index
}

template <class MyType>
void ArithmeticVector<MyType>::operator++(){
	for(int i=0; i < size; i++)
		++ArithmeticVector<MyType>::operator[](i); // increment elements by one by
}

template <class MyType>
void ArithmeticVector<MyType>::operator--(){
	for(int i=0; i < size; i++)
		--ArithmeticVector<MyType>::operator[](i); // decrement elements by one by
}

#endif
