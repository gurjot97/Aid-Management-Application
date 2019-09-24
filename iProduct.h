/*
Student Name: Gurjot Saini
Student ID: 035 053 156

Prof. Name: Peter Liu
Course Code: OOP244-SAB
Section: A

Date: 24/3/19
*/

//included appropriate header files
#include <iostream>
using namespace std;

// header file guard
#ifndef _IPRODUCT_AMA_H_
#define _IPRODUCT_AMA_H_

//namespace "ama" declared, all the code developed is contained within this namespace
namespace ama
{
	//required constants declared
	const int max_length_label = 30;	//This is used when accepting data from user or displaying data to user
	const int max_length_sku = 7;		//This represents the maximum number of characters in an SKU (stock keeping unit)
	const int max_length_name = 75;		//This represents the maximum number of characters for the name of the product
	const int max_length_unit = 10;		//This represents the maximum number of characters in the user descriptor for a product unit
	const int write_condensed = 0;		//This is used to signal what we want the data inserted into a stream in a condensed form
	const int write_table = 1;			//This is used to signal what we want the data inserted into a stream in a table form
	const int write_human = 2;			//This is used to signal what we want the data inserted into a stream in a human readable form
	const double tax_rate = 0.13;		//The current tax rate

	//iProduct class is an interface that exposes the Product hierarchy to client applications
	class iProduct {

		//public members of the class are declared here
	public:
		virtual ostream& write(ostream& os, int writeMode) const = 0;		//This function writes the content of the current instance in the stream received as the first parameter
		virtual istream& read(istream& is, bool interractive) = 0;			//This function reads data from the stream, and stores it in the attributes
		virtual bool operator==(const char* sku) const = 0;					//This query returns true if the string specified in the parameter is the same as the SKU of the current instance; false otherwise
		virtual double total_cost() const = 0;								//This query returns the total cost of all available units of product, including tax
		virtual int qtyNeeded() const = 0;									//This query returns the how many units of product are needed
		virtual int qtyAvailable() const = 0;								//This query returns the how many units of product are available
		virtual const char* name() const = 0;								//This query returns the address of the string storing the name of the product
		virtual int operator+=(int qty) = 0;								//This modifier receives an integer identifying the number of units to be added to the available quantity of product and returns the updated number of units on hand
		virtual bool operator>(const iProduct& other) const = 0;			//This query returns true if the name of the current products is greater than the name of the iProduct received as parameter
		virtual ~iProduct() {}												//Virtual empty-body destructor
	};
}

#endif