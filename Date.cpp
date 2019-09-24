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
#include <cstring>
#include "Date.h"

//namespace "ama" declared, all the code developed is contained within this namespace
namespace ama
{

	//"status" function definition, this function sets the status of the date object to the value of the parameter
	void Date::status(int newStatus) {
		
		dateStatus = newStatus;
	}

	//"mdays" function definition, this function returns the number of days in a given month for a given year
	int Date::mdays(int year, int mon) const
	{
		int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
		int month = mon >= 1 && mon <= 12 ? mon : 13;
		month--;
		return days[month] + int((month == 1)*((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
	}

	//"setDataMembers" function definition, this function assists with initializing the data members of the object
	void Date::setDataMembers(int y, int m, int d) {

		if (y >= min_year && y <= max_year) {
			year = y;

			if (m >= 1 && m <= 12) {
				month = m;

				if (d >= 1 && d <= mdays(year, month)) {
					day = d;

					status(no_error);
				}
				else {
					year = 0;
					month = 0;
					day = 0;

					status(error_day);
				}
			}
			else {
				year = 0;
				month = 0;
				day = 0;

				status(error_mon);
			}
		}
		else {
			year = 0;
			month = 0;
			day = 0;

			status(error_year);
		}
	}

	//default constructor definition: sets the object to an empty state "0000/00/00" and the status to no_error
	Date::Date() {

		year = 0;
		month = 0;
		day = 0;

		status(no_error);
	}

	//custom constructor definition with three arguments: year, month and day
	Date::Date(int y, int m, int d) {
		setDataMembers(y, m, d);
	}

	//"status" function definition, a query that returns an integer representing the status of the current object
	int Date::status() const {
		return dateStatus;
	}

	//"clearError" function definition, a modifier that resets the status of an object to no_error
	void Date::clearError() {
		status(no_error);
	}

	//"isGoodr" function definition, a query that returns true if the object stores a valid date and is not in error mode
	bool Date::isGood() const {
		return (year != 0 && month != 0 && day != 0 && status() == no_error) /* ? true : false */;
	}

	//A modifier that adds to the date stored by the object the number of days specified in the parameter
	Date& Date::operator+=(int days) {

		if (isGood()) {

			if ( ((day + days) >= 1) && ((day + days) <= mdays(year, month)) ) {
				day += days;
			}
			else { status(error_invalid_operation); }
		}
		else { status(error_invalid_operation); }

		return *this;
	}

	//A modifier that adds one day to the date stored by the object(prefix)
	Date& Date::operator++() {
		*this += 1;
		return *this;
	}

	//A modifier that adds one day to the date stored by the object(postfix)
	Date Date::operator++(int) {

		Date dateCopy = *this;
		++(*this);

		return dateCopy;
	}

	//A query that adds to the date stored by the object the number of days specified in the parameter
	//The result is stored in a new object
	Date Date::operator+(int days) const {

		Date dateCopy;

		if (isGood() && ((day + days) >= 1) && ((day + days) <= mdays(year, month)) ) {
			dateCopy = *this;
			dateCopy += days;
		}
		else {
			dateCopy = *this;
			dateCopy.status(error_invalid_operation);
		}

		return dateCopy;
	}

	//A query that returns true if two date objects store the same date
	bool Date::operator==(const Date& rhs) const {
		return ( (year == rhs.year) && (month == rhs.month) && (day == rhs.day) ) /* ? true : false */;
	}

	//A query that returns true if two date objects store different dates
	bool Date::operator!=(const Date& rhs) const {
		return !(*this == rhs);
	}

	//A query that returns true if the current object stores a date that is before the date stored in rhs
	bool Date::operator<(const Date& rhs) const{

		bool isBefore = false;

		if (year < rhs.year) { isBefore = true; }
		
		else if (year == rhs.year) {	
			if (month < rhs.month) { isBefore = true; }

			else if (month == rhs.month) {
				if (day < rhs.day) { isBefore = true; }
			}
		}

		return isBefore;
	}

	//A query that returns true if the current object stores a date that is after the date stored in rhs
	bool Date::operator>(const Date& rhs) const {
		
		bool isBefore = false;

		if (year > rhs.year) { isBefore = true; }

		else if (year == rhs.year) {
			if (month > rhs.month) { isBefore = true; }

			else if (month == rhs.month) {
				if (day > rhs.day) { isBefore = true; }
			}
		}

		return isBefore;
	}

	//A query that returns true if the current object stores a date that is before or equal to the date stored in rhs
	bool Date::operator<=(const Date& rhs) const {
		return ((*this < rhs) || (*this == rhs));
	}

	//A query that returns true if the current object stores a date that is after or equal to the date stored in rhs
	bool Date::operator>=(const Date& rhs) const {
		return ((*this > rhs) || (*this == rhs));
	}

	//A modifier that reads from an input stream a date
	std::istream& Date::read(std::istream& is) {

		int y = 0;
		int m = 0;
		int d = 0;
		char singleChar;

		is.clear();

		is >> y >> singleChar;
		is >> m >> singleChar;
		is >> d;

		if (is.fail() != 0) {

			is.ignore(2000, '\n');
			setDataMembers(0, 0, 0);
			status(error_input);
		}
		else {
			setDataMembers(y, m, d);
		}

		return is;
	}

	//A query that writes the date to an std::ostream object
	std::ostream& Date::write(std::ostream& os) const {
		
		if ( year != 0 && month != 0 && day != 0 ) {

			if (month < 10 && day < 10) {
				os << year << "/0" << month << "/0" << day;
			}
			else if (month < 10 && day >= 10) {
				os << year << "/0" << month << "/" << day;
			}
			else if (month >= 10 && day < 10) {
				os << year << "/" << month << "/0" << day;
			}
			else {
				os << year << '/' << month << '/' << day;
			}
		}
		else {
			os << "0000" << "/" << "00" << "/" << "00";
		}
		
		return os;
	}

	//Reads the date to the first parameter
	std::istream& operator>>(std::istream& is, Date& date) {

		date.read(is);
		return is;
	}

	//Prints the date to the first parameter
	std::ostream& operator<<(std::ostream& os, const Date& date) {

		date.write(os);
		return os;
	}
}
