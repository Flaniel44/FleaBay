/**********************************************************************
Filename:			FleaBay.cpp
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
Purpose: 			Calls the add account functions and login functions.
Creates an account by asking the user for input and using an Account constructor.
Uses ostream<< overloaded operator to report all accounts and their items
Files:				FleaBay.cpp
					FleaBay.h
					Account.cpp
					Account.h
					Item.cpp
					Item.h
					ass2.cpp
Purpose: write the code for a version of the FleaBay assignment that 
is a continuation of assignment 2 and implements code reuse through 
polymorphic inheritance in C++.
*********************************************************************/

#include "Item.h"
#include "Account.h"
#include "FleaBay.h"
#include <iostream>

using namespace std;

/********************************************************************
Function Name: 	FleaBay()
Purpose: 		Default constructor, intitialization
In parameters:	none
Out parameters:	none
Version: 		1.0
Author: 		Daniel Spagnuolo
**********************************************************************/
FleaBay::FleaBay(){
	//initialize variables
	numAccounts = 0;
	accounts = 0;

}

/********************************************************************
Function Name: 	operator[]
Purpose: 		Overloads the [] operator
In parameters:	char pointer to an account ID
Out parameters:	An account
Version: 		1.0
Author: 		Daniel Spagnuolo
**********************************************************************/
Account FleaBay::operator[](char* ID){
	for (unsigned int i=0; i < numAccounts; i++){ //loop through all accounts
		if (strcmp(ID, accounts[i]->getID())==0){ //if ID is matched, return the account
			return *accounts[i];
		}
	}
	// no ID match was found
	Account notFound; //create account using default constructor
	return notFound; //return accout
}

/********************************************************************
Function Name: 	~FleaBay()
Purpose: 		destructs the fleabay object
In parameters:	none
Out parameters:	none
Version: 		1.0
Author: 		Daniel Spagnuolo
**********************************************************************/
FleaBay::~FleaBay(){
	//delete allocated memory
	if (accounts != NULL){ /* Do not free members if array of pointers failed to maloc */
		for (unsigned int i = 0; i < numAccounts; i++){ /* Loop through all accounts, calling the destructor for each account*/
			delete accounts[i];
		}
	}
	delete[](accounts); /* free array of pointers */
}

/********************************************************************
Function Name: 	AddNewAccount
Purpose: 		Add a new Account to the FleaBay
In parameters:	none
Out parameters:	Bool, true if successful, false if not.
Version: 		2.0
Author: 		Daniel Spagnuolo
**********************************************************************/
bool FleaBay::AddNewAccount(){
	int WORD_LENGTH = 30; /*Determines numbers of characters to be allocated */
	ppAccount tempArray; /* temp array for holding new/old accounts. Delete e->accounts, then replace with this array */
	unsigned int i; /* Integer for for loops */
	char* tempID; //temp ID to allow ID to be resized
	char* tempPass; //temp pass to allow pass to be resized
	char* ID; //var for Account contrusctor
	char* Pass; // var for account constructor

	numAccounts +=1; /* Increment number of accounts */

	/* Memory allocations for account */
	tempID = new char[sizeof(char) * WORD_LENGTH];
	tempPass = new char[sizeof(char) * WORD_LENGTH];
	//account->numItems=0;  

	/*Check if malloc worked. If so, continue with adding account */
	if (tempID != NULL && tempPass != NULL){
		cout << "please enter your account ID: ";
		fflush(stdin); 
		fgets(tempID,WORD_LENGTH,stdin); /* fgets instead of scanf to allow for spaces. Max length is a constant 30 */
		strtok(tempID, "\n"); /*Remove any trailing newline characters */
		
		for (i=0;i < numAccounts-1; i++){ /* iterate though all accounts*/
			while (strcmp(accounts[i]->getID(), tempID)==0){ /* Make sure a unique ID is being entered. Loop until unique */
				cout << "Error, Please enter a unique ID: ";
				cin >> tempID;
				strtok(tempID, "\n"); //remove newline
			}/*end while*/
		}/*end for */

		ID = new char[strlen(tempID)+1]; //allocate mem for ID, one space bigger than the string length of the tempID
		strcpy(ID, tempID); //copy temp into ID
		delete[](tempID); //delete temp

		cout << "please enter your password: ";
		
		/* If malloc worked for password, continue to ask for password */
		if (tempPass != NULL){
			fflush(stdin); 
			fgets(tempPass,WORD_LENGTH,stdin);
			strtok(tempPass, "\n"); //remove newline
			Pass = new char[strlen(tempPass)+1]; //allocate mem for pass, one space bigger than the string length of the temppass
			strcpy(Pass, tempPass); //copy temp into pass
			delete[](tempPass); //delete temp
			
		} else{
			cout << "Error allocating memory for ID and Password" << endl;
			return false;
		}
		/*if this is the first account*/
		if (numAccounts == 1){ 
			accounts = new pAccount[numAccounts * sizeof(pAccount)]; /* allocate memory in struct to hold a new account */
			if (accounts != NULL){ /* If malloc woked, assign account to the first index in the array of pointers to accounts */
				accounts[numAccounts -1] = new Account(ID,Pass);
			} else{
				cout << "An error has occured allocating memory for accounts" << endl;
				return false;
			}
		
		}

		if (numAccounts != 1){ /* if this isn't the first account */
			tempArray = accounts; /* Assign tempArray the pointer array in pFleabay */
			accounts = new pAccount[numAccounts * sizeof(pAccount)]; /* malloc for 1 more account */

			if (accounts != NULL){ /*check to see if memory allocated properly */
				accounts[numAccounts -1] = new Account(ID,Pass); /* assign new account to last index */
				for (i = 0; i < numAccounts -1; i++){ /*assign each temp to the now bigger accounts array */
					accounts[i] = tempArray[i];
				}
			} else{
				cout << "An error has occured allocating memory for accounts" << endl;
				return false;
			}
			delete[](tempArray); //delete temp array since dynamic array has been created
		}
		delete[]ID; //delete id now that an object has been made
		delete[]Pass; //delete pass now that an object has been made
	}else{/*End of if statement for null checking */
		cout << "Error allocating memory." << endl;
		delete[]tempPass;
		delete[]tempID;
		return false;
	}
	return true;
}

/********************************************************************
Function Name: 	Login
Purpose: 		Login to a FleaBay account
In parameters:	none
Out parameters:	Bool, true if successful, false if not.
Version: 		1.0
Author: 		Daniel Spagnuolo
**********************************************************************/
bool FleaBay::Login(){
	int WORD_LENGTH = 30; /*max length of account to search for*/
	char i_response; /* Char for menu navigation */
	char add_item = 'n'; //Char for add items question
	char* search = new char[sizeof(char) * 30]; /* string for finding a username to log-in to */
	char* pswd_attempt = new char[sizeof(char) * 30]; /* string for logging in to an account */
	unsigned int i; /* int for a for loop */
	bool found = false; /* Bool for keeping track of whether or not a matching account has been found */

	if (search == NULL || pswd_attempt == NULL){ /* Return from function and cleanup if malloc failed */
		delete[](search);
		delete[](pswd_attempt);
		return false;
	}

	if (numAccounts <=0){ //if there are no account when trying to login, tell user.
		cout << "**NO ACCOUNTS**" << endl;
	}
	cout << "1. Add a new Account" << endl;
	cout << "2. Open an existing Account" << endl;
	cout << "3. Return to Main Menu" << endl;
	cin >> i_response;
	switch(i_response)
	{
	case '1':
		/*adding new account*/
		AddNewAccount();
		break;
	case '2':
		if (numAccounts <=0){  /* only proceed to login if accounts exist */
			cout << "**NO ACCOUNTS**" << endl;
	    } else{
			/*open existing*/
			cout << "please enter your account ID: ";
			fflush(stdin); 
			fgets(search,WORD_LENGTH,stdin); //get ID to search from user
			strtok(search, "\n"); /* remove trailing newline character */
			for (i = 0; i < numAccounts; i++){ /* loop through all accounts */
				if (strcmp(accounts[i]->getID(), search) == 0){ /*If account ID matches search word */
					found = true; //set found to true so that we know an account has been found.
					cout << "please enter your password: ";
					fflush(stdin);
					fgets(pswd_attempt,WORD_LENGTH,stdin);
					strtok(pswd_attempt, "\n"); //trim newline

					if (strcmp(accounts[i]->getPassWord(), pswd_attempt) ==0){ /* check if password is correct */
						if (accounts[i]->getnumItems() == 0){ //if no items, tell user
							cout << "No items in your account" << endl;
						} else if(accounts[i]->getnumItems() > 0){	//if there are items, report them		
							cout<<*accounts[i]; //reports the accounts by calling the ostream overloaded operator
						}
						//menu once logged in
						cout << "Do you wish to change a password? (yes = 'P')" << endl;
						cout << "Do you wish to add another Item (yes = 'Y')" << endl;
						cout << "Want to quit this menu?(yes = 'Q')" << endl;
						cin >> add_item; //get response
						while (add_item != 'Y' && add_item != 'P' && add_item != 'Q'){ //make sure response is valid
							cout << "Enter P, Y, or Q" << endl;
							cin >> add_item;
						}
						while (add_item =='Y' || add_item =='P'){ 
							if (add_item =='Y'){
								accounts[i]->AddItem();		
							} else if (add_item == 'P'){ //change password
								char *tempNewPass = new char[sizeof(char) * WORD_LENGTH]; //temp var to hold password before resize
								char *newPass; //var to hold new password
								char *previousPass = accounts[i]->getPassWord();
								
								cout << "please enter your new password: ";
								fflush(stdin);
								fgets(tempNewPass,WORD_LENGTH,stdin); //get new password
								strtok(tempNewPass, "\n"); //remove trailing newline

								newPass = new char[strlen(tempNewPass)+1]; //+1 because strcpy adds one extra character
								strcpy(newPass, tempNewPass); //copy temp pass into new shortened pass variable
								accounts[i]->getPassWord() = newPass; //use the pointer to a reference to change the password of the account

								delete[] tempNewPass; //cleanup
								delete[] previousPass;

							}
							//menu
							cout << "Do you wish to change a password? (yes = 'P')" << endl;
							cout << "Do you wish to add another Item (yes = 'Y')" << endl;
							cout << "Want to quit this menu?(yes = 'Q')" << endl;
							cin >> add_item; //get response
						}

					} else {
						/* invalid password */
						cout << pswd_attempt << " password doesn't match this ID";
					}
				}
			}
			/* invalid ID */
			if (found == false)
				cout << search << " is invalid ID" << endl;
		}
		
		break;
	case '3':
		/*return */
		break;
	}
	/* free the variables used for logging in */
	delete(search);
	delete(pswd_attempt);
	return true;
}

/********************************************************************
Function Name: 	operator<<
Purpose: 		Overload << to Print all the Accounts
In parameters:	reference to ostream, reference to fleabay
Out parameters: ostream reference
Version: 		1.0
Author: 		Daniel Spagnuolo
**********************************************************************/
ostream operator<<(ostream& os, FleaBay& fleaBay){
	if (fleaBay.numAccounts == 0){ // if there are no accounts, say so.
		os << "**NO ACCOUNTS**" << endl; 
	} else {
		for (unsigned int i = 0; i < fleaBay.numAccounts; i++){ //loop through all accounts
			os << *fleaBay.accounts[i]; //call overloaded << operator for each account
			os << endl;
		}
	}
	return this; //return ostream reference

	
}

