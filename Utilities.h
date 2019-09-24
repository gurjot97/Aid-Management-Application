/*
Student Name: Gurjot Saini
Student ID: 035 053 156

Prof. Name: Peter Liu
Course Code: OOP244-SAB
Section: A

Date: 19/3/19
*/

// header file guard
#ifndef _UTILITIES_AMA_H_
#define _UTILITIES_AMA_H_

//included appropriate header files
#include "Product.h"
#include "Perishable.h"
#include <iostream>
using namespace std;

//namespace "ama" declared
namespace ama
{	
	double& operator+=(double& total, const iProduct& prod);		//Adds the total cost of the product into the first parameter and returns the result
	ostream& operator<<(ostream& out, const iProduct& prod);		//Writes into the first parameter, in a human readable format, the content of the second parameter
	istream& operator>>(istream& in, iProduct& prod);				//Reads from the first parameter a product in interactive mode
	iProduct* createInstance(char tag);								//This function is responsible to dynamically create instances in the Product hierarchy
}

#endif
