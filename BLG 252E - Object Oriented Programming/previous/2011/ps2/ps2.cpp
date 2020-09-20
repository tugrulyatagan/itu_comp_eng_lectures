#include "staff.h"
#include <iostream>
using namespace std;


int main(){
	// creating an array of pointers to address staff member to benefit from polymorphic methods
	StaffMember *sm[5];
	char option;

	// getting information of which type of staff member to add from user
	// and creating object from that type 
	for(int i=0;i<5;i++){
		cout<<"Please choose type of staff member to add?"<<endl;
		cout<<"Salaried Employee[s]"<<endl;
		cout<<"Commission Employee[c]"<<endl;
		cout<<"Piece Worker[p]"<<endl;
		cout<<"Intern[i]"<<endl;
		cout<<"------------------------------------------------"<<endl;
		cin>>option;

		switch(option){
			case 's':
				cout<<"Enter required information for the new salaried employee:"<<endl;
				cout<<"----------------------------------------------------------"<<endl;
				sm[i] = new SalariedEmployee(i+1);
				break;
            case 'c':
				cout<<"Enter required information for the new commission employee:"<<endl;
				cout<<"------------------------------------------------------------"<<endl;
				sm[i] = new CommissionEmployee(i+1);
				break;
            case 'p':
				cout<<"Enter required information for the new piece worker:"<<endl;
				cout<<"-----------------------------------------------------"<<endl;
				sm[i] = new PieceWorker(i+1);
				break;
            case 'i':
				cout<<"Enter required information for the new intern:"<<endl;
				cout<<"---------------------------------------------------"<<endl;
				sm[i] = new Intern(i+1);
				break;
			default:
				cout<<"Wrong option"<<endl;
		}
		
	}

	// use polymorphic print method(and polymorphic pay method inside print) to print information of 
	// different types of staff member

	for(int i=0;i<5;i++){
		cout<<"Staff Member "<<i+1<<endl;
	    cout<<"-----------------------------------------------------"<<endl;
		sm[i]->print();
		cout<<endl;
	}
	
	
	


    return 0;
}
