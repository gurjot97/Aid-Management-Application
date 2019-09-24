/*
Student Name: Gurjot Saini
Student ID: 035 053 156

Prof. Name: Peter Liu
Course Code: OOP244-SAB
Section: A

Date: 10/3/19
*/

//included appropriate header files
#include <iostream>
#include <cstring>
#include "ErrorState.h"

//namespace "ama" declared, all the code developed is contained within this namespace
namespace ama
{

	//This function assists with initializing the data member of the object
	void ErrorState::setDataMember(const char* errorMessage) {

		if (errorMessage != nullptr && errorMessage[0] != '\0') {

			int msgSize = strlen(errorMessage);
			storedMessage = new char[msgSize + 1];
			strcpy(storedMessage, errorMessage);
		}
		else {
			storedMessage = nullptr;
		}
	}

	//No / One argument constructor.This function receives the address of a C - style null terminated string
	ErrorState::ErrorState(const char* errorMessage) {
		setDataMember(errorMessage);
	}

	//This function de-allocates any memory that has been dynamically allocated by the current object
	ErrorState::~ErrorState() {
		delete[] storedMessage;
	}

	//This function return true if the current instance is storing a valid message
	ErrorState::operator bool() const {
		return storedMessage != nullptr;
	}

	//Stores a copy the text received in the parameter
	ErrorState& ErrorState::operator=(const char* pText) {
		message(pText);
		return *this;
	}

	//Stores a copy the text received in the parameter
	void ErrorState::message(const char* pText) {
		
		delete[] storedMessage;
		storedMessage = nullptr;

		setDataMember(pText);
	}

	//This query returns the address of the message stored in the current object
	const char* ErrorState::message() const {
		return *this ? storedMessage : nullptr;
	}

	//Prints the text stored in an ErrorState object to an output stream
	std::ostream& operator<<(std::ostream& os, const ErrorState& errorState) {
		
		if (errorState) {
			os << errorState.message();
		}
		
		return os;
	}
}