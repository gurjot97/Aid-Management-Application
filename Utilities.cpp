/*
Student Name: Gurjot Saini
Student ID: 035 053 156

Prof. Name: Peter Liu
Course Code: OOP244-SAB
Section: A

Date: 19/3/19
*/

//included appropriate header files
#include "Utilities.h"

//namespace "ama" declared
namespace ama
{
	//Adds the total cost of the product into the first parameter and returns the result
	double& operator+=(double& total, const iProduct& prod) {
		total += prod.total_cost();
		return total;
	}

	//Writes into the first parameter, in a human readable format, the content of the second parameter
	ostream& operator<<(ostream& out, const iProduct& prod) {
		prod.write(out, write_human);
		return out;
	}

	//Reads from the first parameter a product in interactive mode
	istream& operator>>(istream& in, iProduct& prod) {
		prod.read(in, true);
		return in;
	}

	//This function is responsible to dynamically create instances in the Product hierarchy
	iProduct* createInstance(char tag) {

		iProduct* product;

		if (tag == 'N' || tag == 'n') {
			product = new Product();
		}
		else if (tag == 'P' || tag == 'p') {
			product = new Perishable();
		}
		else {
			product = nullptr;
		}

		return product;
	}
}