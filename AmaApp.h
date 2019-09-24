/*
Student Name: Gurjot Saini
Student ID: 035 053 156

Prof. Name: Peter Liu
Course Code: OOP244-SAB
Section: A

Date: 29/3/19
*/

// header file guard
#ifndef _AMAAPP_AMA_H_
#define _AMAAPP_AMA_H_

//included appropriate header files
#include "iProduct.h"

//namespace "ama" declared, all the code developed is contained within this namespace
namespace ama
{
	//The AmaApp class has several private member functions and only two public functions
	class AmaApp {

		//data member of the class
		char m_filename[256];			//Holds the name of the text file used to store the product information
		iProduct* m_products[100];		//An array of iProduct pointers
		int m_noOfProducts;				//Number of products (perishable or non-perishable) pointed to by the m_products array

		//public members of the class are declared here
	public:
		AmaApp(const char* fileName);		//A custom constructor that receives as parameter an array of characters representing the filename used by the application
		~AmaApp();							//A destructor that deallocates all dynamic instances stored in the m_products array
		int run();							//Displays the menu, receives the user’s selection, and does the action requested

		//private member functions of the class are declared here
	private:
		AmaApp(const AmaApp&) = delete;					//Prevents AmaApp object to be copied by constructor
		AmaApp& operator=(const AmaApp&) = delete;		//Prevents AmaApp object to be copied by assignment

		void pause() const;								//prints: "Press Enter to continue..."<ENDL> then waits for the user to hit enter
		int menu() const;								//This function displays the menu shown below and waits for the user to select an option
		void loadProductRecords();						//Opens the data file for reading
		void saveProductRecords() const;				//Loops through the m_products array up to m_noOfProducts and stores each of them in a file
		void listProducts() const;						//Prints the list of products in a tabular form
		iProduct* find(const char* sku) const;			//Loops through the m_products array up to m_noOfProducts and checks each of them for the same SKU as the incoming argument
		void addQty(iProduct* product);					//Updates the quantity on hand for an iProduct
		void addProduct(char tag);						//This function should add a new product at the end of the array
	};
}

#endif