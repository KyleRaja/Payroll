#pragma once
#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <string>
#include <iostream>
#include <fstream>

class Employee {
public:
	Employee(int employeeNumber, const std::string& name, const std::string& address, const std::string& phone, double hoursWorked, double hourlyWage);
	int getEmployeeNumber() const;
	std::string getName() const;
	std::string getAddress() const;
	std::string getPhone() const;
	double getHoursWorked() const;
	double getHourlyWage() const;
	void setName(const std::string& name);
	void setAddress(const std::string& address);
	void setPhone(const std::string& phone);
	void setHoursWorked(double hoursWorked);
	void setHourlyWage(double hourlyWage);

	double calcPay() const;
	void printCheck(std::ostream& outStream = std::cout) const;
	void write(std::ofstream& outFile) const;

	static Employee read(std::ifstream& inFile);

private:
	int employeeNumber;
	std::string name;
	std::string address;
	std::string phone;
	double hoursWorked;
	double hourlyWage;
};

#endif   // EMPLOYEE_H