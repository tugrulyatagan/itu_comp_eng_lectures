// OOP 1st Midterm Exam. 09.03.2009
// Question 2
#include <iostream>
#include <string> // String class can also be used 
using namespace std;

class Airplane{
	int id, capacity;
public: 
	Airplane(int, int = 100);

	int getCapacity() const{ return capacity;}
	void print() const;
};

Airplane::Airplane(int n_id, int n_capacity){
	id = n_id;
	capacity = n_capacity;
}

void Airplane::print() const {
	cout << "Airplane information" << endl 
		<< "\tAirplane id: " << id << endl
		<< "\tAirplane capacity: " << capacity << endl;
}

class Flight{

	int source, destination;
	string *psList;
	const Airplane *ap; 
	bool ontime;
	int curCapacity;

public:
	Flight(int, int, const Airplane&);
	Flight(const Flight&);

	void setDelayed(){ontime = false;}

	void print() const;

	~Flight(){		// Destructor is needed
		delete[] psList; 
	}
};

Flight::Flight(int sc, int dst, const Airplane& airp){ 
	source = sc;
	destination = dst;
	ontime = true;
	ap = &airp;			// Instead of a pointer to the airplane, storing the relevant airplane information is also acceptable 
	curCapacity = airp.getCapacity();
	
	psList = new string [curCapacity];

	for (int i= 0; i<curCapacity; i++){
		cout << "Enter passenger [" << i+1 <<"] name: "<< endl;
		cin >> psList[i];
	}
}

Flight::Flight(const Flight& fl){ // Copy constructor is needed  
	source = fl.source;
	destination = fl.destination;
	ontime = fl.ontime;
	ap = fl.ap;
	curCapacity = fl.curCapacity;

	psList = new string [curCapacity];

	for (int i= 0; i<curCapacity; i++){
		psList[i] = fl.psList[i];
	}
}

void Flight::print() const{
	cout << "Flight information: "<< endl;

	ap->print();

	cout << "Source: " << source << endl
			<< "Destination: " << destination << endl;

	if (ontime) 
		cout << "Status: ONTIME" << endl;
	else
		cout << "Status: DELAYED" << endl;

	cout << "Passenger list: " << endl;

	for(int i= 0; i<curCapacity; i++)
		cout << i+1 <<": " << psList[i] << endl;

	cout << endl;
}

int main(){

	Airplane aip1(1,135);   // Airplane:1, Capacity: 135
	aip1.print();
	Airplane aip2 = aip1;
	Airplane aip3(3);       // Airplane:3, Capacity: 100

	Flight fl1(23,45,aip1); // From 23 to 45, by aip1
	Flight fl2 = fl1;

	fl1.print();		// Prints both flight and airplane information
	fl2.setDelayed();
	fl2.print();		// Prints both flight and airplane information

	return 0;
}