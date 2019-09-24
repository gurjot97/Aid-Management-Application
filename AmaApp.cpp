/*
Student Name: Gurjot Saini
Student ID: 035 053 156

Prof. Name: Peter Liu
Course Code: OOP244-SAB
Section: A

Date: 29/3/19
*/

//included appropriate header files
#include <cstring>
#include <fstream>
#include <iomanip>
#include "AmaApp.h"
#include "Utilities.h"

using namespace std;

//namespace "ama" declared, all the code developed is contained within this namespace
namespace ama
{
	//A custom constructor that receives as parameter an array of characters representing the filename used by the application
	AmaApp::AmaApp(const char* fileName) {
		
		int strLen = strlen(fileName);
		strncpy(m_filename, fileName, strLen + 1);
		m_filename[strLen] = '\0';

		for (int i = 0; i < 100; ++i) {
			m_products[i] = nullptr;
		}

		m_noOfProducts = 0;

		loadProductRecords();
	}

	//A destructor that deallocates all dynamic instances stored in the m_products array
	AmaApp::~AmaApp() {

		for (int i = 0; i < 100; ++i) {

			delete m_products[i];
			m_products[i] = nullptr;
		}
	}

	//Displays the menu, receives the user’s selection, and does the action requested
	int AmaApp::run() {

		bool isContinue = true;

		do {

			switch (menu()) {

			case 1:
				listProducts();
				break;

			case 2:

				char SKU[5];
				iProduct* product;

				cout << "Please enter the product SKU: ";
				cin >> SKU;

				cout << endl;

				product = find(SKU);

				if (product != nullptr) {
					cout << *product << endl;
				}
				else {
					cout << "No such product!" << endl;
				}

				cin.ignore(2000, '\n');
				pause();

				break;

			case 3:

				addProduct('N');
				loadProductRecords();

				break;

			case 4:

				addProduct('P');
				loadProductRecords();

				break;

			case 5: 
			{
				char SKU[5];
				SKU[0] = '\0';

				iProduct* product;

				cout << "Please enter the product SKU: ";
				cin >> SKU;
				cout << endl;

				product = find(SKU);

				if (product != nullptr) {
					addQty(product);
				}
				else {
					cout << "No such product!" << endl;
				}

				cout << endl;

				break;
			}

			case 6:
				break;

			case 7:
				break;

			case 0:
				cout << "Goodbye!" << endl;
				isContinue = false;
				break;

			default:
				cout << "~~~Invalid selection, try again!~~~" << endl;
				pause();
			}

		} while (isContinue);

		return 0;
	}

	//prints: "Press Enter to continue..."<ENDL> then waits for the user to hit enter
	void AmaApp::pause() const {
		cout << "Press Enter to continue...";
		cin.ignore(2000, '\n');
		cout << endl;
	}

	//This function displays the menu shown below and waits for the user to select an option
	int AmaApp::menu() const {

		int selection;

		cout << "Disaster Aid Supply Management Program" << endl;
		cout << "--------------------------------------" << endl;
		cout << "1- List products" << endl;
		cout << "2- Search product" << endl;
		cout << "3- Add non-perishable product" << endl;
		cout << "4- Add perishable product" << endl;
		cout << "5- Add to product quantity" << endl;
		cout << "6- Delete product" << endl;
		cout << "7- Sort products" << endl;
		cout << "0- Exit program" << endl;
		cout << "> ";

		cin >> selection;

		if (selection < 0 || selection > 7) {
			selection = -1;
		}

		cin.ignore(2000, '\n');

		return selection;
	}

	//Opens the data file for reading
	void AmaApp::loadProductRecords() {

		for (int i = 0; i < 100; ++i) {

			if (m_products[i] != nullptr) {
				delete m_products[i];
				m_products[i] = nullptr;
			}
		}

		int readingIndex = 0;

		ifstream fin;
		fin.open(m_filename);

		if (fin.is_open()) {

			while (fin) {

				char typeOfProd;
				iProduct* product;

				fin >> typeOfProd;
				product = createInstance(typeOfProd);

				if (product != nullptr) {
					m_products[readingIndex] = product;
					fin.ignore(2000, ',');
					product->read(fin, false);

					if (fin) {
						++readingIndex;
					}
				}
			}

			m_noOfProducts = readingIndex;
			fin.close();
		}
		else {
			fin.close();
		}
	}

	//Loops through the m_products array up to m_noOfProducts and stores each of them in a file
	void AmaApp::saveProductRecords() const {

		ofstream fout;
		fout.open(m_filename);

		for (int i = 0; i < m_noOfProducts; ++i) {
			m_products[i]->write(fout, write_condensed);
			fout << endl;
		}
	}

	//Prints the list of products in a tabular form
	void AmaApp::listProducts() const {

		double totalCost = 0;

		cout << "------------------------------------------------------------------------------------------------" << endl;
		cout << "| Row |     SKU | Product Name     | Unit       |   Price | Tax |   QtyA |   QtyN | Expiry     |" << endl;
		cout << "|-----|---------|------------------|------------|---------|-----|--------|--------|------------|" << endl;

		for (int i = 0; i < m_noOfProducts; ++i) {
			
			cout << "|" << right << setw(4) << (i + 1) << " |";
			m_products[i]->write(cout, write_table);
			cout << endl;

			totalCost += *(m_products[i]);
		}

		cout << "------------------------------------------------------------------------------------------------" << endl;
		cout << "|                                                      Total cost of support ($): | " << right 
			 << setw(10) << fixed << setprecision(2) << totalCost << " |" << endl;
		cout << "------------------------------------------------------------------------------------------------" << endl << endl;

		pause();
	}

	//Loops through the m_products array up to m_noOfProducts and checks each of them for the same SKU as the incoming argument
	iProduct* AmaApp::find(const char* sku) const {

		bool isMatch = false;
		iProduct* matchedProduct = nullptr;

		for (int i = 0; i < m_noOfProducts && !isMatch; ++i) {

			if (*m_products[i] == sku) {

				matchedProduct = m_products[i];
				isMatch = true;
			}
		}

		return matchedProduct;
	}

	//Updates the quantity on hand for an iProduct
	void AmaApp::addQty(iProduct* product) {

		int purchasedItems;

		cout << *product << endl << endl;
		cout << "Please enter the number of purchased items: ";

		cin >> purchasedItems;
	
		if (cin.fail() != 0) {

			cin.clear();
			cout << "Invalid quantity value!" << endl;
		}
		else {

			if ( (product->qtyAvailable() + purchasedItems) <= product->qtyNeeded() ) {
				*product += purchasedItems;
			}
			else {
				int extraItems = (product->qtyAvailable() + purchasedItems) - product->qtyNeeded();
				int neededItems = purchasedItems - extraItems;
				*product += neededItems;

				cout << "Too many items; only "<< neededItems <<" is needed. Please return the extra " << extraItems << " items." << endl;
			}

			saveProductRecords();

			cout << endl << "Updated!" << endl;
		}

		cin.ignore(2000, '\n');
	}

	//This function should add a new product at the end of the array
	void AmaApp::addProduct(char tag) {

		iProduct* product = nullptr;
		product = createInstance(tag);

		if (product != nullptr) {
			cin >> *product;

			if (cin.fail() != 0) {
				
				cin.clear();
				cin.ignore(2000, '\n');
				
				cout << endl << *product << endl << endl;
			}
			else {
				m_products[m_noOfProducts++] = product;
				saveProductRecords();
				cout << endl << "Success!" << endl << endl;
			}
		}
	}


}