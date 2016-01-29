/**********************************************************************
Filename:			Item.cpp
Version: 			2.0                                         
Author:				Daniel Spagnuolo                                            
Student No:  		040 768 219                                              
Course Name/Number:	C++   CST8219                                 
Lab Sect: 			302                                                      
Assignment #:		3
Assignment name:	FleaBay with Polymorphic Inheritance
Due Date:			December 5th 2015                                           
Submission Date:	December 5th 2015
Professor:			Andrew Tyler                                           
Purpose: 			Constructing, destructing, and printing of items				                      
*********************************************************************/

#include "Item.h"
#include "Account.h"
#include "FleaBay.h"
#include <iostream>
#include <iomanip> //for setting decimal precision

using namespace std;

/********************************************************************
Function Name: 	Item()
Purpose: 		Default constructor, intitialization
In parameters:	none
Out parameters:	none
Version: 		1.0
Author: 		Daniel Spagnuolo
**********************************************************************/
Item::Item(){
	//init to zero
	description = 0;
	price = 0;
}

/********************************************************************
Function Name: 	Item()
Purpose: 		Copy constructor, does a deep copy of the given reference to Item object
In parameters:	Reference to Item 
Out parameters:	none
Version: 		1.0
Author: 		Daniel Spagnuolo
**********************************************************************/
Item::Item(Item& item){
	description = new char[strlen(item.description) + 1]; // alloc space for item member
	strcpy(description, item.description); //copy reference despription into item desc. mem

	price = item.price; //copy price
}

/********************************************************************
Function Name: 	Item()
Purpose: 		Overloaded constructor, creates an object fro the passed parameters
In parameters:	char pointer description and Password used for creating the object 
Out parameters:	none
Version: 		1.0
Author: 		Daniel Spagnuolo
**********************************************************************/
Item::Item(char* descirption, double price){
	Item::description = new char[strlen(descirption)+1]; // alloc space for item member
	strcpy(Item::description, descirption); //copy param into member

	Item::price = price; //assign param to member
}

/********************************************************************
Function Name: 	~Item()
Purpose: 		destructs the Item object
In parameters:	none
Out parameters:	none
Version: 		1.0
Author: 		Daniel Spagnuolo
**********************************************************************/
Item::~Item(){ 
	if (description != NULL && description != nullptr){
		delete[] description; //delete description
	}
}

/********************************************************************
Function Name: 	operator<<
Purpose: 		Print all item members
In parameters:	reference to ostream, reference to item
Out parameters: ostream reference
Version: 		1.0
Author: 		Daniel Spagnuolo
**********************************************************************/
ostream& operator<<(ostream& os, Item& item){ 
	item.Report();
	os << " " << item.description << ", cost = $" << fixed << std::setprecision(2) << item.price << endl; //format print for item members
	return os; //return reference to ostream
}


// -------------------------------SUBCLASS--------------------------------

/******************************************************************************
Function Name:		FoodAndBeverages::FoodandBeverage()
Purpose:			Overloaded constructor for the FoodAndBeverages subclass.
In Parameters:		Date, char pointer, double
Out Parameters:		none
Version:			1.0
Author:				Daniel Spagnuolo
******************************************************************************/
FoodAndBeverages::FoodAndBeverages(Date expire, char* description, double price) : Item(description, price){
	expiryDate.day = expire.day;
	expiryDate.month = expire.month;
	expiryDate.year = expire.year;
}

/******************************************************************************
Function Name:		FoodAndBeverages::FoodandBeverage()
Purpose:			Copy constructor for the FoodAndBeverages subclass.
In Parameters:		FoodAndBeverages reference
Out Parameters:		none
Version:			1.0
Author:				Daniel Spagnuolo
******************************************************************************/
FoodAndBeverages::FoodAndBeverages(FoodAndBeverages& item) : Item(item){
	expiryDate.day = item.expiryDate.day;
	expiryDate.month = item.expiryDate.month;
	expiryDate.year = item.expiryDate.year;
}

/******************************************************************************
Function Name:		FoodAndBeverages::Report()
Purpose:			Prints subclass info
In Parameters:		none
Out Parameters:		none
Version:			1.0
Author:				Daniel Spagnuolo
******************************************************************************/
void FoodAndBeverages::Report(){
	cout << " Food and Beverages Report" << endl
	<< "Closing Date: " << expiryDate.day << "/" << expiryDate.month << "/"
	<< expiryDate.year << endl;
}

// -------------------------------SUBCLASS--------------------------------

/******************************************************************************
Function Name:		ToysAndHobbies::ToysAndHobbies()
Purpose:			Overloaded constructor for the ToysAndHobbies subclass.
In Parameters:		int, char pointer, double
Out Parameters:		none
Version:			1.0
Author:				Daniel Spagnuolo
******************************************************************************/
ToysAndHobbies::ToysAndHobbies(int age, char* description, double price) : Item(description, price) {
	suitableAge = age;
}

/******************************************************************************
Function Name:		ToysAndHobbies::ToysAndHobbies()
Purpose:			Copy constructor for the ToysAndHobbies subclass.
In Parameters:		ToysAndHobbies reference
Out Parameters:		none
Version:			1.0
Author:				Daniel Spagnuolo
******************************************************************************/
ToysAndHobbies::ToysAndHobbies(ToysAndHobbies& item) : Item(item) {
	suitableAge = item.suitableAge;
}

/******************************************************************************
Function Name:		ToysAndHobbies::Report()
Purpose:			Prints subclass info
In Parameters:		none
Out Parameters:		none
Version:			1.0
Author:				Daniel Spagnuolo
******************************************************************************/
void ToysAndHobbies::Report(){
	cout << " Toys AndHobbies Report" << endl
	<< "Suitable Age Group: " << suitableAge << " years." << endl;
}

// -------------------------------SUBCLASS--------------------------------

/******************************************************************************
Function Name:		Deals::Deals()
Purpose:			Overloaded Constructor for the Deals subclass.
In Parameters:		Date, char pointer, double
Out Parameters:		none
Version:			1.0
Author:				Daniel Spagnuolo
******************************************************************************/
Deals::Deals(Date endDate, char* description, double price) : Item(description, price){
	closingDate.day = endDate.day;
	closingDate.month = endDate.month;
	closingDate.year = endDate.year;
}

/******************************************************************************
Function Name:		Deals::Deals()
Purpose:			Copy constructor for the Deals object.
In Parameters:		Deals reference
Out Parameters:		none
Version:			1.0
Author:				Daniel Spagnuolo
******************************************************************************/
Deals::Deals(Deals& item) : Item(item){
	closingDate.day = item.closingDate.day;
	closingDate.month = item.closingDate.month;
	closingDate.year = item.closingDate.year;
}

/******************************************************************************
Function Name:		Deals::Report()
Purpose:			Print Deals info
In Parameters:		none
Out Parameters:		none
Version:			1.0
Author:				Daniel Spagnuolo
******************************************************************************/
void Deals::Report(){
	cout << " Deal Report" << endl
	<< "Closing Date: " << closingDate.day << "/" << closingDate.month << "/"
	<< closingDate.year << endl;
}