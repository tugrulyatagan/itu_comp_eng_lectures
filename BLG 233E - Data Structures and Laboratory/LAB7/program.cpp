#include <iostream>
#include <string>
#include <iomanip>
#include "stack.h"
#include "queue.h"
using namespace std;

void init();
void generate();
void take_car();
void show();
void exit();
int find(char *);

Stack *A = new Stack[AREA_NUMBER];
Queue T;

int main(){
	init();
	generate();
	show();

	take_car();

	exit();
	return EXIT_SUCCESS;
}


void generate(){
	int count;
	cout << "Enter number of car for initilization:  ";
	cin >> count;
	if (count > AREA_NUMBER * AREA_CAPATICTY){
		cout << "Too large number" <<  endl;
		return;
	}
	for(int k = 0; k < count; k++){
		Node *newCar = new Node;
		newCar->data = new char[PLATE_LENGHT];
		itoa(k + 1,newCar->data,10);
		for(int i = 0; i < AREA_NUMBER; i++)
			if(k % AREA_NUMBER == i) A[i].push(newCar);
	}
}

void take_car(){
	char *new_plate = new char[PLATE_LENGHT];
	cout << "Enter plate:  ";
	cin.ignore(1000, '\n');
	cin.getline(new_plate,PLATE_LENGHT);
	if(!find(new_plate)){
		cout << "Car is not in park" << endl;
	}

	for(int i = 0; i < AREA_NUMBER; i++){
		if(find(new_plate) == i){

		}
	}
}

int find(char *plate){
	for(int i = 0; i < AREA_NUMBER; i++)
		if(A[i].search(plate)) return i;
	return 0;
}

void show(){
	for(int i = 0; i < AREA_NUMBER; i++){
		cout << "                 ____________________________" << endl;
		cout << "Area" << i + 1 << " :           "; A[i].print(); cout << endl;
	}
	cout << "                 ____________________________|_________" << endl;
	cout << "Temporary Area:   "; T.print(); cout << endl;
	cout << "                 ______________________________________" << endl;
}

void init(){
	cout << "CAR PARKING PROGRAM" << endl;
	for(int i = 0; i < AREA_NUMBER; i++)
		A[i].create();
	T.create();
}

void exit(){
	for(int i = 0; i < AREA_NUMBER; i++)
		A[i].close();
	T.close();
}

