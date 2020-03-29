#include <iostream>
#include <fstream>
#include "employee.h"

using namespace std;

// write and read methods
void writeToFile();
void readFromFile();

int main() {
	char userInput;
	cout << "This program has two options :" << endl
		<< "1 - Create a data file, or" << endl
		<< "2 - Read data from a file and print paychecks." << endl
		<< "Please enter (1) to create a file or (2) to print checks: ";
	cin >> userInput;

	if (userInput == '1') { // if user selects to create file
		writeToFile(); // calls method
	}
	else if (userInput == '2') { // if user selects to read file 
		readFromFile(); // calls method
	}
	system("pause");
	return 0;
}

void writeToFile() { // method to store data in file. 
	cout << "\nPlease enter a file name: " << endl;
	string fileName;
	cin >> fileName; // user input of file name
	ofstream outFile(fileName); // object outFile of class ofstream with fileName as the argument. 
	if (outFile.fail()) { // error handling. 
		cout << "Couldn't open file for output." << endl;
		outFile.clear(); // clearing file 
		outFile.close(); // closing file
		return;
	}

	Employee joe(37, "Joe Brown", "123 Main St.", "123-6788", 45.00, 10.00); // creating object joe of class Employee and passing data.
	Employee sam(21, "Sam Jones", "45 East State", "661-9000", 30.00, 12.00);
	Employee mary(15, "Mary Smith", "12 High Street", "401-8900", 40.00, 15.00);

	// calls write method with user file as the argument.
	joe.write(outFile); 
	sam.write(outFile);
	mary.write(outFile);

	outFile.close();

	cout << "Data file created ... you can now run option 2." << endl;
}

void readFromFile() { // method to read file
	cout << "\nPlease enter a file name: " << endl;
	string fileName;
	cin >> fileName; // user enters file name already created.
	ifstream inFile(fileName); // reading the data inside the file
	if (inFile.fail()) { // error handling 
		cout << "Couldn't open file for input." << endl;
		inFile.clear(); // clear to free up memory
		inFile.close();
		return;
	}

	try { // try block 
		// public static read method called with argument as inFile. Since its static it can be directly called with out an object. 
		Employee joe = Employee::read(inFile);
		Employee sam = Employee::read(inFile);
		Employee mary = Employee::read(inFile);

		joe.printCheck();
		sam.printCheck();
		mary.printCheck();
	}
	catch (exception& e) { // catches std(standard) exceptions such as runtime error(bugs), overflow error(infinite loop, out of range number) etc. 
		cout << e.what() << endl; // what() is a method of the exception class and returns the cause of the exception
	}
	catch (...) { // catch all. Default exception handler. Does not give specific reason for error. 
		cout << "Unknown error." << endl; 
	}

	inFile.clear(); // clearing file
	inFile.close(); // closing file 
}