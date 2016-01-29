#include <iostream> 
using namespace std;

typedef class FleaBay
{
	unsigned int numAccounts;
	ppAccount accounts;
	bool AddNewAccount();
public:
	FleaBay();						
	~FleaBay();
	bool Login();				
	Account operator[](char*);
	friend ostream& operator<<(ostream&,FleaBay&);
}* pFleaBay;