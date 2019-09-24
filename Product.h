/*
Student Name: Gurjot Saini
Student ID: 035 053 156

Prof. Name: Peter Liu
Course Code: OOP244-SAB
Section: A

Date: 19/3/19
*/

//included appropriate header files
#include "iProduct.h"
#include "ErrorState.h" 

// header file guard
#ifndef _PRODUCT_AMA_H_
#define _PRODUCT_AMA_H_

//namespace "ama" declared, all the code developed is contained within this namespace
namespace ama
{
	//Product class is a concrete class that encapsulates the general information for an AMA product
	class Product : public iProduct {
		
		//data members of the class
		const char m_typeOfProd;				//A constant character that indicates the type of the product
		char m_SKU[max_length_sku + 1];			//A character array that holds the product’s SKU (stock keeping unit)
		char m_Unit[max_length_unit + 1];		//A character array that describes the product’s unit
		char* m_Name;							//A pointer that holds the address of a C-style string in dynamic memory containing the name of the product
		int m_QntityOnHand;						//An integer that holds the quantity of the product currently on hand (available)
		int m_QntityNeeded;						//An integer that holds the quantity of the product needed
		double m_Price;							//A double that holds the price of a single unit of the product before any taxes
		bool m_TaxStatus;						//A bool that identifies the taxable status of the product; its value is true if the product is taxable
		ErrorState errorState;					//An ErrorState object that holds the error state of the Product object

		//private member functions of the class
		void setDataMember(const char* SKU, const char* name, const char* unit, 
						   double price, int qntityNeeded, 
						   int qntityOnHand, bool taxStatus);	//This function assists with initializing the data members of the object

		//protected members of the class are declared here
	protected:
		void message(const char* pText);		//This function receives the address of a C-style null-terminated string holding an error message and stores that message in the ErrorState object
		bool isClear() const;					//This query returns true if the ErrorState attribute contains no error message, false otherwise
	
		//public members of the class are declared here
	public:
		Product(const char typeOfProd = 'N');					//This constructor optionally receives a character that identifies the product type
		Product(const char* SKU, const char* name, const char* unit, 
				double price = 0, int qntityNeeded = 0, 
				int qntityOnHand = 0, bool taxStatus = true);	//A Custom Constructor with 7 arguments: This constructor receives in its seven parameters values
		Product(const Product&);								//The Copy Constructor
		~Product();												//The Destructor
		Product& operator=(const Product&);						//The Copy Assignment Operator

		int operator+=(int qty);						//This modifier receives an integer identifying the number of units to be added to the available quantity attribute
		bool operator==(const char* sku) const;			//This query returns true if the string specified in the parameter is the same as the string stored in the SKU attribute
		bool operator> (const char* sku) const;			//This query returns true if the SKU attribute from the current instance is greater than the string stored at the received address
		bool operator> (const iProduct& other) const;	//This query returns true if the name of the current object is greater than the name of the Product received as parameter object
		int qtyAvailable() const;						//This query returns the value of the attribute storing how many units of product are available
		int qtyNeeded() const;							//This query returns the value of the attribute storing how many units of product are needed
		double total_cost() const;						//This query returns the total cost of all available units of product, including tax
		bool isEmpty() const;							//This query returns true if the object is in the empty state; false otherwise
		const char* name() const;						//This query returns the address of the string storing the name of the product

		std::istream& read(std::istream& in, bool interractive);		//This function reads data from the stream, and stores it in the attributes
		std::ostream& write(std::ostream& out, int writeMode) const;	//This function writes the content of the current instance in the stream received as the first parameter
	};
}

#endif