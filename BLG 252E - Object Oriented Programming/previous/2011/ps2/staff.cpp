#include "staff.h"

// Constructor and Method Bodies of StaffMember class
//___________________________________________________________________________________________

// Constructor
StaffMember::StaffMember(unsigned int id_in){
	// unique id's in ascending order
	companyID = id_in;
	cout<<"Enter name: "<<endl;
	cin>>name;
	cout<<"Enter surname: "<<endl;
	cin>>surname;
} 
// Methods to set attributes
void StaffMember::setCompanyID(unsigned int id_in){companyID = id_in;}
void StaffMember::setName(string name_in){name = name_in;}
void StaffMember::setSurname(string surname_in){surname = surname_in;}
// Methods to get attributes
unsigned int StaffMember::getCompanyID() const{return companyID;}
string StaffMember::getName() const{return name;}
string StaffMember::getSurname() const{return surname;}
// Print method
void StaffMember::print() const{
	cout<<"Company ID: "<<companyID<<endl
		<<"Full Name: "<<name<<" "<<surname<<endl;
}


// Constructor and Method Bodies of Intern class
//___________________________________________________________________________________________

// Constructor getting all required information via keyboard
Intern::Intern(unsigned int id_in) : StaffMember(id_in){ 
		cout<<"Enter school name: "<<endl;
		cin>>schoolName;
} 
// Method to set additional attribute: schoolName
void Intern::setSchoolName(string schoolname_in){schoolName = schoolname_in;}
// Method to get additional attribute: schoolName
string Intern::getSchoolName() const{return schoolName;}
// Polymorphic print method
void Intern::print() const{
	StaffMember::print();
	cout<<"School Name: "<<schoolName<<endl;
}


// Constructor and Method Bodies of Employee class
//___________________________________________________________________________________________

// Constructor getting all required information via keyboard
Employee::Employee(unsigned int id_in) : StaffMember(id_in){ 
		cout<<"Enter social security number: "<<endl;
		cin>>socialSecurityNumber;
} 
// Method to set additional attribute: socialSecurityNumber
void Employee::setSocialSecurityNumber(string ssn_in){socialSecurityNumber = ssn_in;}
// Method to get additional attribute: socialSecurityNumber
string Employee::getSocialSecurityNumber() const{return socialSecurityNumber;}
// Polymorphic print method
void Employee::print() const{
	StaffMember::print();
	cout<<"Social Security Number: "<<socialSecurityNumber<<endl;
}
// Pay method to calculate and return weekly payment
double Employee::pay() const{
	return 0.00;
}


// Constructor and Method Bodies of SalariedEmployee class
//___________________________________________________________________________________________

// Constructor getting all required information via keyboard
SalariedEmployee::SalariedEmployee(unsigned int id_in) : Employee(id_in){ 
		cout<<"Enter weekly salary($): "<<endl;
		cin>>weeklySalary;
} 
// Method to set additional attribute: weeklySalary
void SalariedEmployee::setWeeklySalary(double salary_in){weeklySalary = salary_in;}
// Method to get additional attribute: weeklySalary
double SalariedEmployee::getWeeklySalary() const{return weeklySalary;}
// Polymorphic print method
void SalariedEmployee::print() const{
	Employee::print();
	cout<<"Weekly Salary: $"<<weeklySalary<<endl;
	cout<<"Earned: $"<<pay()<<" this week"<<endl;
}
// Pay method to calculate and return weekly payment
double SalariedEmployee::pay() const{
	return weeklySalary;
}


// Constructor and Method Bodies of CommissionEmployee class
//___________________________________________________________________________________________

// Constructor getting all required information via keyboard
CommissionEmployee::CommissionEmployee(unsigned int id_in) : Employee(id_in){
		cout<<"Enter commission rate: "<<endl;
		cin>>commissionRate;
		cout<<"Enter weekly profit from sales($): "<<endl;
		cin>>weeklySales;
}
// Method to set additional attribute: commissionRate
void CommissionEmployee::setCommissionRate(double crate_in){commissionRate = crate_in;}
// Method to get additional attribute: commissionRate
double CommissionEmployee::getCommissionRate() const{return commissionRate;}
// Method to set additional attribute: weeklySales
void CommissionEmployee::setWeeklySales(unsigned int sales_in){weeklySales = sales_in;}
// Method to get additional attribute: weeklySales
unsigned int CommissionEmployee::getWeeklySales() const{return weeklySales;}
// Polymorphic print method
void CommissionEmployee::print() const{
	Employee::print();
	cout<<"Commission Rate: "<<100*commissionRate<<"%"<<endl;
	cout<<"Weekly Sales: $"<<weeklySales<<endl;
	cout<<"Earned: $"<<pay()<<" this week"<<endl;
}
// Pay method to calculate and return weekly payment
double CommissionEmployee::pay() const{
	return commissionRate * weeklySales;
}


// Constructor and Method Bodies of PieceWorker class
//___________________________________________________________________________________________

// Constructor getting all required information via keyboard
PieceWorker::PieceWorker(unsigned int id_in) : Employee(id_in){ 
		cout<<"Enter wage per piece produced($): "<<endl;
		cin>>wagePerPiece;
		cout<<"Enter number of pieces produced this week: "<<endl;
		cin>>piecesProduced;
}
// Method to set additional attribute: wagePerPiece
void PieceWorker::setWagePerPiece(double wpp_in){wagePerPiece = wpp_in;}
// Method to get additional attribute: wagePerPiece
double PieceWorker::getWagePerPiece() const{return wagePerPiece;}
// Method to set additional attribute: weeklySales
void PieceWorker::setPiecesProduced(unsigned int pieces_in){piecesProduced = pieces_in;}
// Method to get additional attribute: weeklySales
unsigned int PieceWorker::getPiecesProduced() const{return piecesProduced;}
// Polymorphic print method
void PieceWorker::print() const{
	Employee::print();
	cout<<"Wage Per Piece: $"<<wagePerPiece<<endl;
	cout<<"Number of Pieces Produced This Week: "<<piecesProduced<<endl;
	cout<<"Earned: $"<<pay()<<" this week"<<endl;
}
// Pay method to calculate and return weekly payment
double PieceWorker::pay() const{
	return wagePerPiece * piecesProduced;
}
