#ifndef STAFF_H
#define STAFF_H

#include <iostream>
#include <string>
using namespace std;

// Base class declaration
class StaffMember{
	// Protected data attributes can be reached directly from derived classes
protected:
	unsigned int companyID;
	string name;
	string surname;
public:
	// Constructor getting all required information via keyboard
	StaffMember(unsigned int id_in);
	// Methods to set attributes
	void setCompanyID(unsigned int id_in);
	void setName(const string& name_in);
	void setSurname(const string& surname_in);
	// Methods to get attributes
	unsigned int getCompanyID() const;
	const string& getName() const;
	const string& getSurname() const;
	// Polymorphic print method
	virtual void print() const;
};

// Intern class derived from StaffMember class
class Intern: public StaffMember{
	string schoolName;
public:
	// Constructor getting all required information via keyboard
	Intern(unsigned int id_in);
	// Method to set additional attribute: schoolName
	void setSchoolName(const string& schoolname_in);
	// Method to get additional attribute: schoolName
	const string& getSchoolName() const;
	// Polymorphic print method
	void print() const;
};

// Employee class derived from StaffMember class
class Employee: public StaffMember{
	string socialSecurityNumber;
public:
	// Constructor getting all required information via keyboard
	Employee(unsigned int id_in);
	// Method to set additional attribute: socialSecurityNumber
	void setSocialSecurityNumber(const string& ssn_in);
	// Method to get additional attribute: socialSecurityNumber
	const string& getSocialSecurityNumber() const;
	// Polymorphic print method
	void print() const;
	// Polymorphic pay method to calculate and return weekly payment (Pure virtual)
	virtual double pay() const = 0;
};

// SalariedEmployee class derived from Employee class
class SalariedEmployee: public Employee{
	double weeklySalary;
public:
	// Constructor getting all required information via keyboard
	SalariedEmployee(unsigned int id_in);
	// Method to set additional attribute: weeklySalary
	void setWeeklySalary(double salary_in);
	// Method to get additional attribute: weeklySalary
	double getWeeklySalary() const;
	// Polymorphic print method
	void print() const;
	// Polymorphic pay method to calculate and return weekly payment
	double pay() const;
};

// CommissionEmployee class derived from Employee class
class CommissionEmployee: public Employee{
	double commissionRate;
	unsigned int weeklySales;
public:
	// Constructor getting all required information via keyboard
	CommissionEmployee(unsigned int id_in);
	// Method to set additional attribute: commissionRate
	void setCommissionRate(double crate_in);
	// Method to get additional attribute: commissionRate
	double getCommissionRate() const;
	// Method to set additional attribute: weeklySales
	void setWeeklySales(unsigned int sales_in);
	// Method to get additional attribute: weeklySales
	unsigned int getWeeklySales() const;
	// Polymorphic print method
	void print() const;
	// Polymorphic pay method to calculate and return weekly payment
	double pay() const;
};

// PieceWorker class derived from Employee class
class PieceWorker: public Employee{
	double wagePerPiece;
	unsigned int piecesProduced;
public:
	// Constructor getting all required information via keyboard
	PieceWorker(unsigned int id_in);
	// Method to set additional attribute: wagePerPiece
	void setWagePerPiece(double wpp_in);
	// Method to get additional attribute: wagePerPiece
	double getWagePerPiece() const;
	// Method to set additional attribute: piecesProduced
	void setPiecesProduced(unsigned int pieces_in);
	// Method to get additional attribute: piecesProduced
	unsigned int getPiecesProduced() const;
	// Polymorphic print method
	void print() const;
	// Polymorphic pay method to calculate and return weekly payment
	double pay() const;
};

#endif
