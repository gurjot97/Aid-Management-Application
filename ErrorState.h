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

//
// header file guard
#ifndef _ERRORSTATE_AMA_H_
#define _ERRORSTATE_AMA_H_

//namespace "ama" declared, all the code developed is contained within this namespace
namespace ama
{

	//ErrorState class definition, manages the error state of client code and encapsulates the last error message
	class ErrorState {

		//data members of the class
		char* storedMessage;				//stores the address of the error message

		//private member functions of the class
		void setDataMember(const char*);	//This function assists with initializing the data member of the object

	//public members of the class are declared here
	public:

		explicit ErrorState(const char* errorMessage = nullptr);	//No / One argument constructor.This function receives the address of a C - style null terminated string
		ErrorState(const ErrorState& other) = delete;				//This class should not allow copying of any ErrorState object
		ErrorState& operator=(const ErrorState& other) = delete;	//This class does not allow copy assignment
		~ErrorState();												//This function de-allocates any memory that has been dynamically allocated by the current object
		operator bool() const;										//This function return true if the current instance is storing a valid message
		ErrorState& operator=(const char* pText);					//Stores a copy the text received in the parameter
		void message(const char* pText);							//Stores a copy the text received in the parameter
		const char* message() const;								//This query returns the address of the message stored in the current object
	};

	std::ostream& operator<<(std::ostream&, const ErrorState&);		//Prints the text stored in an ErrorState object to a stream
}

#endif