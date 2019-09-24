/*
Student Name: Gurjot Saini
Student ID: 035 053 156

Prof. Name: Peter Liu
Course Code: OOP244-SAB
Section: A

Date: 19/3/19
*/

//included appropriate header files
#include <iostream>
#include <iomanip>
#include <cstring>
#include "Product.h"

//namespace "ama" declared, all the code developed is contained within this namespace
namespace ama
{
	//This function receives the address of a C-style null-terminated string holding an error message and stores that message in the ErrorState object
	void Product::message(const char* pText) {
		errorState.message(pText);
	}

	//This query returns true if the ErrorState attribute contains no error message, false otherwise
	bool Product::isClear() const {
		return !errorState;
	}

	//This constructor optionally receives a character that identifies the product type
	Product::Product(const char typeOfProd) : m_typeOfProd(typeOfProd)
	{
		setDataMember(nullptr, nullptr, nullptr, 0, 0, 0, false);
	}

	//A Custom Constructor with 7 arguments: This constructor receives in its seven parameters values
	Product::Product(const char* SKU, const char* name, const char* unit,
		double price, int qntityNeeded,int qntityOnHand, bool taxStatus) : m_typeOfProd('N')
	{	
		setDataMember(SKU, name, unit, price, qntityNeeded, qntityOnHand, taxStatus);
	}

	//This function assists with initializing the data members of the object
	void Product::setDataMember(const char* SKU, const char* name, const char* unit,
		double price, int qntityNeeded, int qntityOnHand, bool taxStatus) 
	{
		if (name != nullptr && name[0] != '\0') {

			int nameLength;
			strlen(name) < max_length_name ? nameLength = strlen(name) : nameLength = max_length_name;
			m_Name = new char[nameLength + 1];

			strncpy(m_Name, name, nameLength);
			m_Name[nameLength] = '\0';

			strcpy(m_SKU, SKU);
			strcpy(m_Unit, unit);
			m_Price = price;
			m_QntityNeeded = qntityNeeded;
			m_QntityOnHand = qntityOnHand;
			m_TaxStatus = taxStatus;
		}
		else {
			strcpy(m_SKU, "\0");
			m_Name = nullptr;
			strcpy(m_Unit, "\0");
			m_Price = 0;
			m_QntityNeeded = 0;
			m_QntityOnHand = 0;
			m_TaxStatus = false;
		}
	}

	//The Copy Constructor
	Product::Product(const Product& product) : m_typeOfProd('N') 
	{
		setDataMember(product.m_SKU, product.m_Name, product.m_Unit, 
					  product.m_Price, product.m_QntityNeeded, 
					  product.m_QntityOnHand, product.m_TaxStatus);
	}

	//The Destructor
	Product::~Product() {
		delete[] m_Name;
		m_Name = nullptr;
	}

	//The Copy Assignment Operator
	Product& Product::operator=(const Product& product) {

		if (this != &product) {

			delete[] m_Name;

			setDataMember(product.m_SKU, product.m_Name, product.m_Unit,
				product.m_Price, product.m_QntityNeeded,
				product.m_QntityOnHand, product.m_TaxStatus);
		}
		return *this;
	}

	//This modifier receives an integer identifying the number of units to be added to the available quantity attribute
	int Product::operator+=(int qty) {

		if (qty > 0) { m_QntityOnHand += qty; }
		return m_QntityOnHand;
	}

	//This query returns true if the string specified in the parameter is the same as the string stored in the SKU attribute
	bool Product::operator==(const char* sku) const {
		return strcmp(m_SKU, sku) == 0 ? true : false;
	}

	//This query returns true if the SKU attribute from the current instance is greater than the string stored at the received address
	bool Product::operator> (const char* sku) const {
		return strcmp(m_SKU, sku) > 0 ? true : false;
	}

	//This query returns true if the name of the current object is greater than the name of the Product received as parameter object
	bool Product::operator> (const iProduct& other) const {
				
		return strcmp(m_Name, other.name()) > 0 ? true : false;
	}

	//This query returns the value of the attribute storing how many units of product are available
	int Product::qtyAvailable() const {
		return m_QntityOnHand;
	}

	//This query returns the value of the attribute storing how many units of product are needed
	int Product::qtyNeeded() const {
		return m_QntityNeeded;
	}

	//This query returns the total cost of all available units of product, including tax
	double Product::total_cost() const {
		return  m_TaxStatus == true ? ( m_QntityOnHand * m_Price) * (1.00 + tax_rate) :  m_QntityOnHand * m_Price;
	}

	//This query returns true if the object is in the empty state; false otherwise
	bool Product::isEmpty() const {
		return m_Name == nullptr ? true : false;
	}

	//This query returns the address of the string storing the name of the product
	const char* Product::name() const {
		return m_Name;
	}

	//This function reads data from the stream, and stores it in the attributes
	std::istream& Product::read(std::istream& in, bool interractive) {

		char SKU[max_length_sku + 1];
		char name[max_length_name + 1];
		char unit[max_length_unit + 1];
		double price;
		int qntityNeeded;
		int qntityOnHand;
		bool taxStatus;
		char yesOrNo;
		char singleChar;

		in.clear();

		if (interractive == false) {
			
			in.getline(SKU, max_length_unit, ',');
			in.getline(name, max_length_name, ',');
			in.getline(unit, max_length_unit, ',');
			in >> price >> singleChar;
			in >> taxStatus >> singleChar;
			in >> qntityOnHand >> singleChar;
			in >> qntityNeeded;

			if (in.fail() != 0) {

				in.ignore(2000, '\n');
				setDataMember(nullptr, nullptr, nullptr, 0, 0, 0, false);
			}
			else {
				setDataMember(SKU, name, unit, price, qntityNeeded, qntityOnHand, taxStatus);
			}
		}
		else {

			int i = 1;

			do {

				if (i == 1) {
					std::cout << std::right << std::setw(max_length_label) << "Sku: ";
					in >> SKU;
				}
				else if (i == 2) {
					std::cout << std::right << std::setw(max_length_label) << "Name (no spaces): ";
					in >> name;
				}
				else if (i == 3) {
					std::cout << std::right << std::setw(max_length_label) << "Unit: ";
					in >> unit;
				}
				else if (i == 4) {
					std::cout << std::right << std::setw(max_length_label) << "Taxed? (y/n): ";

					in >> yesOrNo;

					if (yesOrNo == 'y' || yesOrNo == 'Y') {
						taxStatus = true;
					}
					else if (yesOrNo == 'n' || yesOrNo == 'N') {
						taxStatus = false;
					}
					else {
						in.setstate(std::ios::failbit);
						taxStatus = false;
					}
				}
				else if (i == 5) {
					std::cout << std::right << std::setw(max_length_label) << "Price: ";
					in >> price;
				}
				else if (i == 6) {
					std::cout << std::right << std::setw(max_length_label) << "Quantity on hand: ";
					in >> qntityOnHand;
				}
				else if (i == 7) {
					std::cout << std::right << std::setw(max_length_label) << "Quantity needed: ";
					in >> qntityNeeded;
				}

				if (in.fail() == 0) { ++i; }

			} while (i <= 7 && in.fail() == 0);


			if (in.fail() != 0) {

				if (i == 4) {
					errorState.message("Only (Y)es or (N)o are acceptable!");
				}
				else if (i == 5) {
					errorState.message("Invalid Price Entry!");
				}
				else if (i == 6) {
					errorState.message("Invalid Quantity Available Entry!");
				}
				else if (i == 7) {
					errorState.message("Invalid Quantity Needed Entry!");
				}

				in.ignore(2000, '\n');
				setDataMember(nullptr, nullptr, nullptr, 0, 0, 0, false);
			}
			else {
				setDataMember(SKU, name, unit, price, qntityNeeded, qntityOnHand, taxStatus);
			}
		}

		return in;
	}

	//This function writes the content of the current instance in the stream received as the first parameter
	std::ostream& Product::write(std::ostream& out, int writeMode) const {

		if (errorState) {
			out << errorState;
		}
		else if (!isEmpty()) {

			if (writeMode == write_condensed) {
				
				out << m_typeOfProd << ",";
				out << m_SKU << ",";
				out << m_Name << ",";
				out << m_Unit << ",";
				out << std::fixed << std::setprecision(2) << m_Price << ",";
				out << (m_TaxStatus == true ? 1 : 0) << ",";
				out << m_QntityOnHand << ",";
				out << m_QntityNeeded;
			}
			else if (writeMode == write_table) {
				
				out << " " << std::right << std::setw(max_length_sku) << m_SKU << " " << "|";

				if (strlen(m_Name) <= 16) {
					out << " " << std::left << std::setw(16) << m_Name << " " << "|";
				}
				else {

					char tempName[16 + 1];
					strncpy(tempName, m_Name, 13);
					tempName[13] = '\0';
					strcat(tempName, "...");
					tempName[16] = '\0';

					out << " " << std::left << std::setw(16) << tempName << " " << "|";
				}

				out << " " << std::left << std::setw(10) << m_Unit << " " << "|";
				out << " " << std::right << std::setw(7) << std::fixed << std::setprecision(2) << m_Price << " " << "|";
				out << " " << std::right << std::setw(3) << (m_TaxStatus == true ? "yes" : "no") << " " << "|";
				out << " " << std::right << std::setw(6) << m_QntityOnHand << " " << "|";
				out << " " << std::right << std::setw(6) << m_QntityNeeded << " " << "|";
			}
			else if (writeMode == write_human) {

				out << std::right << std::setw(max_length_label) << "Sku: " << m_SKU << std::endl;
				out << std::right << std::setw(max_length_label) << "Name: " << m_Name << std::endl;
				out << std::right << std::setw(max_length_label) << "Price: " << std::fixed << std::setprecision(2) << m_Price <<  std::endl;
				out << std::right << std::setw(max_length_label) << "Price after Tax: " << std::fixed << std::setprecision(2) << (m_TaxStatus == true ? (double)(m_Price * (1.00 + tax_rate)) : m_Price) << std::endl;
				out << std::right << std::setw(max_length_label) << "Quantity Available: " << m_QntityOnHand << " " << m_Unit << std::endl;
				out << std::right << std::setw(max_length_label) << "Quantity Needed: " << m_QntityNeeded << " " << m_Unit << std::endl;
			}
		}

		return out;
	}
}