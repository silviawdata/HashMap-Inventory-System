#include "hashMap.h"
#include <string>
#include <iostream>
using std::cout;
using std::endl;
using std::string;

int main()
{
	hashMap<string, int> people;

	people.insert("Tom", 12);
	people.insert("Patrick", 15);
	people.insert("Warren", 1);
	people.insert("Peyton", 18);

	cout << people.getValue("Tom") << endl;
	cout << people.getValue("Warren") << endl;
	cout << people.getValue("Peyton") << endl;
	cout << people.getValue("Patrick") << endl;

	return 0;
}
