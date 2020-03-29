#include <iostream>
#include <ios>
#include <fstream>
#include <string>
#include <stdexcept>
#include "employee.h"

using namespace std;


// Employee constructor(instance method). Used to initialize class objects and initialize values of the object. 
Employee::Employee(int employeeNumber, const string& name, const string& address, const string& phone, double hoursWorked, double hourlyWage) // pass by const reference since we are not modifying.
	: name(name), address(address), phone(phone) {
	if ((employeeNumber < 0) || (hoursWorked < 0.0) || (hourlyWage < 0.0)) // if hours worked or wage is less than 0, error is thrown. These are values of the objects in main.cpp
		throw out_of_range("employeeNumber, hoursWorked, and hourlyWage must be >= 0.");

	// assigning local variable to data member with the this pointer. 
	this->employeeNumber = employeeNumber; 
	this->hoursWorked = hoursWorked;
	this->hourlyWage = hourlyWage;
}

int Employee::getEmployeeNumber() const {
	return employeeNumber;
}

string Employee::getName() const {
	return name;
}

string Employee::getAddress() const {
	return address;
}

string Employee::getPhone() const {
	return phone;
}

double Employee::getHoursWorked() const {
	return hoursWorked;
}

double Employee::getHourlyWage() const {
	return hourlyWage;
}

void Employee::setName(const string& name) {
	this->name = name;
}

void Employee::setAddress(const string& address) {
	this->address = address;
}

void Employee::setPhone(const string& phone) {
	this->phone = phone;
}

void Employee::setHoursWorked(double hoursWorked) {
	if (hoursWorked < 0.0)
		throw out_of_range("hoursWorked must be >= 0.");

	this->hoursWorked = hoursWorked;
}

void Employee::setHourlyWage(double hourlyWage) {
	if (hourlyWage < 0.0)
		throw out_of_range("hourlyWage must be >= 0.");

	this->hourlyWage = hourlyWage;
}


double Employee::calcPay() const { // method to calculate weekly paycheck amount.
	double baseHours = (hoursWorked >= 40.0) ? 40.0 : hoursWorked; // assigns base hours to 40.0
	double overTime = (hoursWorked >= 40.0) ? (hoursWorked - 40.0) : 0; // overtime 
	double grossPay = (baseHours * hourlyWage) + (overTime * (hourlyWage * 1.5)); // gross pay

	double fedTax = grossPay * 0.20; // 20%
	double stateTax = grossPay * 0.075; // 7.5%

	return grossPay - fedTax - stateTax; // returns gross pay - taxes
}

// Uses <iostream>
// outStream is default to cout
void Employee::printCheck(ostream& outStream) const { 
	outStream.setf(ios::showpoint); // ensures double and floating point numbers are printed with decimal numbers
	outStream.setf(ios::fixed); // format option of decimal numbers
	outStream.precision(2); // 2 decimals after the number (12.00)

	outStream << endl
		<< ".................................Payroll Dept................................." << endl
		<< "Pay to the order of " << name << "....................................$" << calcPay() << endl
		<< endl
		<< "United Community Credit Union" << endl
		<< ".............................................................................." << endl
		<< endl
		<< "Hours worked: " << hoursWorked << endl
		<< "Hourly wage: " << hourlyWage << endl
		<< endl;
}

// Uses <fstream>
void Employee::write(ofstream& outFile) const { // object passed as reference since there is no copy constructor. const because we are not modifying the data members, only inserting information into file. 
	outFile.exceptions(ios::failbit); // function signifiying an I/O error. Most likely because of invalid data (letters were found when trying to read a number).
	outFile << employeeNumber << ',' << name << ',' << address << ',' << phone << ',' << hoursWorked << ',' << hourlyWage << endl; // using the stream insertion operator to write to file.
}

// Public static function. Uses <fstream>, <iostream>, <ios>
Employee Employee::read(ifstream& inFile) {
	string field[6]; // setting the list with value 6
	int employeeNumber;
	string name, address, phone;
	double hoursWorked, hourlyWage;

	inFile.exceptions(ios::failbit); // exception handling.

	for (int i = 0; i < 5; i++) {
		getline(inFile, field[i], ','); // getline is somewhat misleading here, deliminate when it sees a comma. Alternative to using the extraction operator >> 

	}
	getline(inFile, field[5]);    // last item, so don't deliminate by a comma this time


	// How this should look: ID, name, address, phone, hoursWorked, hourlyWage.
	employeeNumber = stoi(field[0]);
	name = field[1];
	address = field[2];
	phone = field[3];
	hoursWorked = stod(field[4]);
	hourlyWage = stod(field[5]);

	return Employee(employeeNumber, name, address, phone, hoursWorked, hourlyWage);
}