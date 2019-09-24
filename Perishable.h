/*
Student Name: Gurjot Saini
Student ID: 035 053 156

Prof. Name: Peter Liu
Course Code: OOP244-SAB
Section: A

Date: 29/3/19
*/

// header file guard
#ifndef _PERISHABLE_AMA_H_
#define _PERISHABLE_AMA_H_

//included appropriate header files
#include "Product.h"
#include "Date.h"

//namespace "ama" declared, all the code developed is contained within this namespace
namespace ama
{
	//Perishable class is a concrete class that encapsulates the general information for an AMA product
	class Perishable : public Product {

		//data member of the class
		Date date;			//An attribute of type Date to store the expiry date for a perishable product

		//public members of the class are declared here
	public: 
		Perishable();		//A default constructor. This constructor should call the one-parameter constructor from the base, and pass 'P' for the record tag
		
		std::ostream& write(std::ostream& out, int writeMode) const;	//This function writes the content of the current instance in the stream received as the first parameter
		std::istream& read(std::istream& in, bool interractive);		//This function reads data from the stream, and stores it in the attributes
	};
}

#endif