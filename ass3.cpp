#include <crtdbg.h>
#include "Item.h"
#include "Account.h"
#include "FleaBay.h"

#include <iostream>
using namespace std;

int main(void)
{
	bool bRunning = true;
	char id[256];
	char response;
	FleaBay e;


 	while(bRunning)
	{
		cout<<"\nPlease enter your choice"<<endl;
		cout<<"1. FleaBay Login"<<endl;
		cout<<"2. FleaBay Report"<<endl;
		cout<<"3. Report an Account"<<endl;
		cout<<"4. Quit"<<endl;

		cin>>response;
		cin.ignore(256,'\n');

		switch(response)
		{
		case '1':
			if(!e.Login())
				return 1;
			break;
		case '2':
			cout<<e;
			break;
		case '3':
			cout<<"please enter the account id: ";
			cin.getline(id,256,'\n');
			cout<<e[id];
			break;
		case '4':
			bRunning=false;
			break;
		default:
			cout<<"invalid choice";
		}
	}
	return 0;
}