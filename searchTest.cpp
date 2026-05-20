#include "hashMap.h"
#include <string>
#include <iostream>
using std::cout;
using std::endl;
using std::string;

int main()
{
	hashMap<string, string> people(100);

	people.insert("Tom",  "Patriots");
	people.insert("Peyton", "Colts");
	people.insert("Patrick", "Chiefs");
	people.insert("Warren", "Oilers");
	people.insert("Donovan",  "Eagles");
	people.insert("Joe",  "49ers");
	people.insert("Lamar",  "Ravens");

	cout << people.getValue("Lamar") << endl;
	cout << people.getValue("Donovan") << endl;
	cout << people.getValue("Joe") << endl;
	cout << people.getValue("Patrick") << endl;
	cout << people.getValue("Warren") << endl;
	cout << people.getValue("Tom") << endl;
	cout << people.getValue("Peyton") << endl;

	cout << endl;

	if (people.find("Tom"))
		cout << "Tom is found" << endl;

	if (!people.find("Steve"))
		cout << "Steve is not found" << endl;

	if (people.find("Warren"))
		cout << "Warren is found" << endl;

	if (people.find("Joe"))
		cout << "Joe is found" << endl;

	if (!people.find("Dan"))
		cout << "Dan is not found" << endl;

	if (people.find("Lamar"))
		cout << "Lamar is found" << endl;

	if (people.find("Peyton"))
		cout << "Peyton is found" << endl;

	if (!people.find("John"))
		cout << "John is not found" << endl;

	if (!people.find("Ben"))
		cout << "Ben (Roethlisberger) is not found" << endl;

	if (people.find("Patrick"))
		cout << "Tom is found" << endl;

	if (people.find("Donovan"))
		cout << "Donovan is found" << endl;

	return 0;
}
