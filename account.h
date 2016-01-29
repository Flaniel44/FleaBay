#include <iostream> 
using namespace std;

typedef class Account
{
	char* ID;
	char* PassWord;
	unsigned int numItems;
	ppItem items;
public:
	Account();
	Account(Account&);
	Account(char*,char*);
	~Account();
	char* getID(){return ID;}
	char*& getPassWord();
	unsigned int getnumItems(){return numItems;}
	void AddItem();	
	friend ostream& operator<<(ostream&, Account&);
}*pAccount,**ppAccount;