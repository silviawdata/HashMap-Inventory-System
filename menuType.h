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




*/
