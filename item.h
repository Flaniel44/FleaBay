#include <iostream> 
using namespace std;

typedef class Item
{
	char* description;
	double price;
	friend ostream& operator<<(ostream&, Item&); 
public:
	Item();
	Item(Item&);
	Item(char*,double);
	virtual~Item(); 
	virtual void Report(void) = 0;
}*pItem,**ppItem;

struct Date
{		
	unsigned int day, month, year;
};

class FoodAndBeverages:public Item
{
	Date expiryDate;
public:
	FoodAndBeverages(Date, char*, double);
	FoodAndBeverages(FoodAndBeverages&);
	void Report(void);
};

class ToysAndHobbies:public Item
{
	int suitableAge;
public:
	ToysAndHobbies(int, char*, double);
	ToysAndHobbies(ToysAndHobbies&);
	void Report(void);
};

class Deals:public Item
{
	Date closingDate;
public:
	Deals(Date, char*, double);
	Deals(Deals&);
	void Report(void);
};