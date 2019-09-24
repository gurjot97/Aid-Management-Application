/*
Student Name: Gurjot Saini
Student ID: 035 053 156

Prof. Name: Peter Liu
Course Code: OOP244-SAB
Section: A

Date: 29/3/19
*/

//included appropriate header files
#include <iostream>
#include <iomanip>
#include "Perishable.h"

using namespace std;

//namespace "ama" declared, all the code developed is contained within this namespace
namespace ama
{
	//A default constructor. This constructor should call the one-parameter constructor from the base, and pass 'P' for the record tag
	Perishable::Perishable() : Product('P') {}

	//This function writes the content of the current instance in the stream received as the first parameter
	std::ostream& Perishable::write(std::ostream& out, int writeMode) const {

		Product::write(out, writeMode);

		if ( isClear() && !(isEmpty()) ) {

			if (writeMode == write_condensed) {
				out << "," << date;
			}
			else if (writeMode == write_table) {
				out << " " << date << " " << "|";
			}
			else if (writeMode == write_human) {
				out << right << setw(max_length_label) << "Expiry Date: " << date << endl;
			}
		}

		return out;
	}

	//This function reads data from the stream, and stores it in the attributes
	std::istream& Perishable::read(std::istream& in, bool interractive) {

		Date tempDate;

		Product::read(in, interractive);

		if (interractive == true) {

			cout << right << setw(max_length_label) << "Expiry date (YYYY/MM/DD): ";
			in >> tempDate;

			if (tempDate.status() != no_error) {
				
				in.setstate(ios::failbit);

				switch (tempDate.status()) {

					case error_year:
						message("Invalid Year in Date Entry");
						break;

					case error_mon:
						message("Invalid Month in Date Entry");
						break;

					case error_day:
						message("Invalid Day in Date Entry");
						break;

					case error_input:
						message("Invalid Date Entry");
						break;
				}
			}
			else {
				date = tempDate;
			}
		}
		else if (interractive == false) {

			in.ignore(2000, ',');
			date.read(in);
			in.ignore(2000, '\n');
		}

		return in;
	}
}