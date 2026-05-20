#ifndef MENUTYPE_H
#define MENUTYPE_H

#include <string>

class menuType
{
private:
	std::string name;
	double price;
	int quantity;
public:
	menuType() : name(""), price(0), quantity(0) {}
	menuType(std::string n, double p, int q) : name(n),
		price(p), quantity(q) {}

	std::string getName() const { return name; }
	double getPrice() const { return price; }
	int getQuantity() const { return quantity; }

	menuType updateQuantity(int amount)
	{
		quantity = (quantity < amount) ? 0 : quantity - amount;

		return *this;
	}
};

#endif



/*NOTES ON HOW TO IMPLEMENT MAIN.CPP

Our csv file, has 3 variables: name, price quantity.

so basically parsing the file like in a previous code, i have done before. this is associted 
with the menu type header file file. 

parsing the file with comas. 

can use the find function of the string. 
can use strodfunction to convert a string into a decimal. remainder can be passed into an stoi function 
then after each component, call the menu type constructor to initalize the object.
then insert this object into the map using the name as the key. insert into the map one by one. 



we can use a vector to store the items list. 







*/
