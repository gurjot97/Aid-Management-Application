/*
Student Name: Gurjot Saini
Student ID: 035 053 156

Prof. Name: Peter Liu
Course Code: OOP244-SAB
Section: A

Date: 8/3/19
*/

//included appropriate header files
#include <iostream>

//
// header file guard
#ifndef _DATE_AMA_H_
#define _DATE_AMA_H_

//namespace "ama" declared, all the code developed is contained within this namespace		 
namespace ama
{

	//required constants declared
	const int min_year = 2019;	//This represents the minimum year acceptable for a valid date
	const int max_year = 2028;	//This represents the maximum year for a valid date
	const int no_error = 0;		//A date object with this status is either in a safe empty state or holds a valid date
	const int error_year = 1;	//The client has attempted to set an invalid year for the date object
	const int error_mon = 2;	//The client has attempted to set an invalid month for the date object
	const int error_day = 3;	//The client has attempted to set an invalid day for the date object
	const int error_invalid_operation = 4;	//The client has attempted to perform an invalid operation on the date object
	const int error_input = 5;	//The date object failed to read data from an input steam(stream data was in the wrong format)

	//Date class definition, the Date class encapsulates a date that is readable by an std::istream and printable by an std::ostream
	class Date {

		//data members of the class
		int year;	//an integer with a value between constant variables "min_year" and "max_year", inclusive
		int month;	//an integer with a value between 1 and 12
		int day;	//an integer with a value between the minimum and maximum number of days in the specific month
		int dateStatus;	  //an integer used by the client to determine if the object contains a valid date

		//private member functions of the class
		void status(int);	//This function sets the status of the date object to the value of the parameter
		int mdays(int, int) const;	//This function returns the number of days in a given month for a given year
		void setDataMembers(int, int, int); //This function assists with initializing the data members of the object   
	
	//public members of the class are declared here
	public:

		Date();	//default constructor declaration: sets the object to an empty state "0000/00/00" and the status to no_error
		Date(int, int, int);	//custom constructor declaration with three arguments: year, month and day
		
		int status() const;		//A query that returns an integer representing the status of the current object
		void clearError();		//A modifier that resets the status of an object to no_error
		bool isGood() const;	//A query that returns true if the object stores a valid date and is not in error mode
		
		Date& operator+=(int);		//A modifier that adds to the date stored by the object the number of days specified in the parameter
		Date& operator++();			//A modifier that adds one day to the date stored by the object(prefix)
		Date operator++(int);		//A modifier that adds one day to the date stored by the object(postfix)
		Date operator+(int) const;	//A query that adds to the date stored by the object the number of days specified in the parameter, the result is stored in a new object
		
		bool operator==(const Date&) const;	//A query that returns true if two date objects store the same date
		bool operator!=(const Date&) const;	//A query that returns true if two date objects store different dates
		bool operator<(const Date&) const;  //A query that returns true if the current object stores a date that is before the date stored in rhs
		bool operator>(const Date&) const;	//A query that returns true if the current object stores a date that is after the date stored in rhs
		bool operator<=(const Date&) const;	//A query that returns true if the current object stores a date that is before or equal to the date stored in rhs
		bool operator>=(const Date&) const; //A query that returns true if the current object stores a date that is after or equal to the date stored in rhs
		
		std::istream& read(std::istream&);			//A modifier that reads from an input stream a date
		std::ostream& write(std::ostream&) const;	//A query that writes the date to an std::ostream object
	};
	
	std::istream& operator>>(std::istream&, Date&);	//Reads the date to the first parameter
	std::ostream& operator<<(std::ostream&, const Date&); //Prints the date to the first parameter

}

#endif