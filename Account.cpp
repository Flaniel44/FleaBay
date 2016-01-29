/**********************************************************************
Filename:			Account.cpp
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
Purpose: 			Contains consturctors and destructors for account objects.
Asks user for input for creating an item for that specific account.
*********************************************************************/

#include "Item.h"
#include "Account.h"
#include "FleaBay.h"
#include <iostream>

using namespace std;

/********************************************************************
Function Name: 	Account()
Purpose: 		Default constructor, intitialization
In parameters:	none
Out parameters:	none
Version: 		1.0
Author: 		Daniel Spagnuolo
**********************************************************************/
Account::Account(){
	//intitialize variables. Invalid ID since overloaded constructor must be used.
	ID = new char[strlen("Invalid ID")+1];
	strcpy(ID,"Invalid ID");
	
	PassWord = new char[strlen("Invalid ID")+1];
	strcpy(PassWord,"Invalid ID");

	numItems = 0;
	items = 0;
}

/********************************************************************
Function Name: 	Account()
Purpose: 		Copy constructor, does a deep copy of the given reference to account object
In parameters:	Reference to account 
Out parameters:	none
Version: 		2.0
Author: 		Daniel Spagnuolo
**********************************************************************/
Account::Account(Account& account){
	//allocate space for ID member
	ID = new char[strlen(account.ID) + 1];
	strcpy(ID, account.ID); //copy ID from reference into member ID

	//allocate space for pass member
	PassWord = new char[strlen(account.PassWord) + 1];
	strcpy(PassWord, account.PassWord);//copy pass from reference into member pass

	numItems = account.numItems;

	//perform a deep copy of item subclasses, using dynamic cast to determine item subtype
	items = new pItem[numItems];
	for (unsigned int i = 0; i < numItems; i++){
		if(dynamic_cast<Deals*>(account.items[i])){
			items[i] = new Deals(*dynamic_cast<Deals*>(account.items[i]));
		}
		else if (dynamic_cast<FoodAndBeverages*>(account.items[i])){
			items[i] = new FoodAndBeverages(*dynamic_cast<FoodAndBeverages*>(account.items[i]));
		}
		else {
			items[i] = new ToysAndHobbies(*dynamic_cast<ToysAndHobbies*>(account.items[i]));
		}
	}
}

/********************************************************************
Function Name: 	Account()
Purpose: 		Overloaded constructor, creates an object fro the passed parameters
In parameters:	char pointer ID and Password used for creating the object 
Out parameters:	none
Version: 		1.0
Author: 		Daniel Spagnuolo
**********************************************************************/
Account::Account(char* ID, char* PassWord){
	//allocate space for ID
	Account::ID = new char[strlen(ID)+1];
	strcpy(Account::ID, ID); //assign parameter to ID

	//allocate space for pass
	Account::PassWord = new char[strlen(PassWord)+1];
	strcpy(Account::PassWord, PassWord); //assign parameter to pass

	//init to zero
	numItems = 0;
	items = 0;
}

/********************************************************************
Function Name: 	~Account()
Purpose: 		destructs the Account object
In parameters:	none
Out parameters:	none
Version: 		1.0
Author: 		Daniel Spagnuolo
**********************************************************************/
Account::~Account(){
	if (ID != NULL) //only delete if pointer points to something
		delete[]ID; //delete ID
	if (PassWord!=NULL)
		delete[]PassWord; //delete pass
	if (items != NULL){ /* Do not free members if array of pointers failed to maloc */
		for (unsigned int i = 0; i < numItems; i++){ /* Loop through all accounts, freeing Item pointers*/
			delete items[i];
		}
	}
	delete[](items); /* free array of pointers */
}

/********************************************************************
Function Name: 	AddItem
Purpose: 		Add a new item to the Account
In parameters:	none
Out parameters:	none
Version: 		2.0
Author: 		Daniel Spagnuolo
**********************************************************************/
void Account::AddItem(){
	int WORD_LENGTH = 30; /*Determines numbers of characters to be allocated */
	ppItem tempArray; /* temp array for holding new/old accounts. Delete e->accounts, then replace with this array */
	unsigned int i; /* Integer for for loops */
	char* tempDescription; //temp char to hold value so that description char can be sized properly
	char* Description; //char for holding the item description field for the overloaded item constructor
	double price;
	char itemType = 0;
	Date date = {0,0,0};
	int ageGroup = 0;

	numItems ++; /* Increment number of items */

	/* Memory allocations for item fields */
	tempDescription = new char[sizeof(char) * WORD_LENGTH];

	/*Check if malloc worked. If so, continue with adding account */
	if (tempDescription != NULL){
		cout << "Enter the new Item Description:" << endl;
		fflush(stdin); 
		fgets(tempDescription,WORD_LENGTH,stdin);  /* fgets instead of scanf to allow for spaces. Max length is a constant 30 */
		strtok(tempDescription, "\n"); /*Remove any trailing newline characters */

		Description = new char[(strlen(tempDescription))+1]; //size description to the string length of temp +1
		strcpy(Description, tempDescription); //copy temp into description
		delete[](tempDescription); //delete temp

		cout << "Please enter the new item price: ";
		cin >> price; //get price from user
		while (cin.fail() || price < 0){ //check that price is valid
			cin.clear(); // clear the error flags
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ignore the rest of what's left in the input buffer
			cout << "Error, enter a valid price: ";
			cin >> price; //get price again
		}

		cout << "What category of item is it? ('F' = FoodAndBeverages,  'T' =ToysAndHobbies, 'D' = Deals)" << endl;
		cin >> itemType;
		while (itemType != 'F' && itemType != 'T' && itemType != 'D'){
			cout << "Error, enter a valid category: ('F' = FoodAndBeverages,  'T' =ToysAndHobbies, 'D' = Deals) " << endl;
			cin >> itemType; //get price again
		}
		if (toupper(itemType) == 'F'){
			cout << "please enter the expiry date as: day month year ";
			cin >> date.day >> date.month >> date.year;
		} else if (toupper(itemType) == 'T'){
			cout << "Please enter the appropriate age group ( e.g. 6): ";
			cin >> ageGroup;
			while (cin.fail() || ageGroup < 0){ //check that age is valid
				cin.clear(); // clear the error flags
				cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ignore the rest of what's left in the input buffer
				cout << "Error, enter a valid age: ";
				cin >> ageGroup; //get age again
			}
		} else if (toupper(itemType) == 'D'){
			cout << "Please enter the date the deal expires as: day month year ";
			cin >> date.day >> date.month >> date.year;
		}


		/*if this is the first account*/
		if (numItems == 1){ 
			items = new pItem[numItems * sizeof(pItem)]; /* allocate memory in struct to hold a new account */
			if (items != NULL){ /* If malloc woked, assign account to the first index in the array of pointers to accounts */
				if (toupper(itemType) == 'F'){
					items[numItems -1] = new FoodAndBeverages(date, Description, price);
				} else if (toupper(itemType) == 'T'){
					items[numItems -1] = new ToysAndHobbies(ageGroup, Description, price);
				} else if (toupper(itemType) == 'D'){
					items[numItems -1] = new Deals(date, Description, price);
				}
			} else{
				cout << "An error has occured allocating memory for items" << endl;
			}
		
		}
		if (numItems != 1){ /* if this isn't the first account */
			tempArray = items; /* Assign tempArray the pointer array in pFleabay */
			items = new pItem[numItems * sizeof(pItem)]; /* malloc for 1 more account */

			if (items != NULL){ /*check to see if memory allocated properly */
				if (toupper(itemType) == 'F'){
					items[numItems -1] = new FoodAndBeverages(date, Description, price);
				} else if (toupper(itemType) == 'T'){
					items[numItems -1] = new ToysAndHobbies(ageGroup, Description, price);
				} else if (toupper(itemType) == 'D'){
					items[numItems -1] = new Deals(date, Description, price);
				}
				for (i = 0; i < numItems -1; i++){ /*assign each temp to the now bigger accounts array */
					items[i] = tempArray[i];
				}
			} else{
				cout << "An error has occured allocating memory for items" << endl;
			}
			delete[](tempArray);
		}
		delete[]Description;
	}else{/*End of if statement for null checking */
		cout << "Error allocating memory." << endl;
		delete[]tempDescription;
	}
}

char*& Account::getPassWord(){
	return PassWord;
}


/********************************************************************
Function Name: 	operator<<
Purpose: 		Print an account with its items
In parameters:	reference to ostream, reference to account
Out parameters: ostream reference
Version: 		1.0
Author: 		Daniel Spagnuolo
**********************************************************************/
ostream& operator<<(ostream& os, Account& account){
	os << "Account ID: " << account.getID() << endl; //print account ID
	for (unsigned int i=0; i < account.numItems; i++){ //for every item,
		os << "Item "<<i<<": "; 
		os<<*account.items[i]; //call osteam<< for each item to print its contents
	}
	return os; //return ostream reference

}