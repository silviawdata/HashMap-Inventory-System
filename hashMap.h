#ifndef HASHMAP_H
#define HASHMAP_H

#include <cstdlib>
#include <string>
#include "menuType.h"

template <class t1, class t2>
class hashMap
{
private:
	class node
	{
	public:
		node(t1 k) : key(k), value(t2()) {}
		node(t1 k, t2 v) : key(k), value(v) {}
		t1 key;
		t2 value;
	};

	node ** table1;
	node ** table2;
	std::size_t capacity;
	std::size_t items1; // a count
	std::size_t items2; // a count

	std::size_t hash1(std::string); //param: string
	std::size_t hash2(std::string);

	void resize(std::size_t);

	std::size_t lookup(t1 k);

public:
	hashMap(std::size_t = 7);
	~hashMap();
	bool find(t1 k);
	void insert(t1 k, t2 v);
	void update(t1 k, t2 v);
	t2 getValue(t1 k);
};

#endif


///notes for assignment 05
/*

constructor: basic setup
items 1, 2 = 0;
allocate array [table1] = capacity and [table2]
where is equals 7. 
alocate to nullptr / two arrays 
table = new node*[capacity];

for (size_t i=0; i< capacity; i++)
table[i] = nullptr;

for deallocation we must traverse throught table 1 and 2 
for deleting items
dealloate each node independently then the table. 
same concept as deallocating an array. 

each node contains a key value pair. 
	std::size_t items1; // a count
	std::size_t items2; // a count
we always increment it by 1 everytime we insert something
table 1 and table 2 will have the same compacity 
t1 = string and t2 = int

remember find/insert function from class
find function is a double hashing technique

insert function(t1 k,t2 v){
size_t = index;
index = h(k) % capacity;
table[index] //insert a node in this linked list
size++;
if(table [index] = = nullptr){
table [index] = new node();
table[index]
items++;
}
if(table[index]-> key == k)
return;
i++;
index = (index + i) % capacity;
}

t2 getValue(t1 k){

size_t index = h(k) % capactity
size_t i =0;
if(table[index]==nullptr)
return t2();
if(table[index]-> key == k){

return table[index]->value;
i++;
index = (index = i) % capacity;
}

}
///LOOK UP FUNCTION
look up (t1 k){
size_t index = 0;
index = (hash1(k) + 1 * hash2(k)) % capactiy;

for(node*i = table[index]; i!=nullprt; i = i -> link){

if(i -> key == k){
return true;
}
return false;
}

where i is your collision counter initially set to 0 and increments by one after a collision, using the
index computed you search in table1[index], if the location is vacant, return the index, if this
location is not vacant but the node in this location has a matching key, return the index. If a collision
was found in table1[index], perform the same steps on table2[index], if a collision was also present
in table2, increment i by 1, recompute the index and perform the same procedure, until a vacancy or
match is found
bool hashMap<t1

example:

///////////////////////////////////////////////////////////////////

almost the same as last assignment for get value

Hash Map Function:
size_t hashMap<t1, t2>::hash1(string k) - first hash function, for a given key as a string, it
returns the following sum
possible for loop here to transverse the string:
'H' * 10^0 + 'e' * 10^1 + 'l'* 10^2 + etc.

i
size_t hashMap<t1, t2>::hash2(string k) - second hash function, for a given key as a string, it
returns the following sum

opposite direction

//so basically we want larger values to not have same results,
// so we do not cause any collisions. 



code:

node*i = table[1]
if(i->key == k)
node*i = table;
if(i->key == k)
i = i ->link;

//Insert function/find function//get value funtion//
we must use the look up function inside


resize function??
need to allocate two tables
where we are passing capacity into this function but passing within our insert function

you pass in some ammount the capacity. 
table 1 and table we multiple it by capacity time the amount. 

so we call the resize function within our insert function 
so if we insert, our table becomes 20% full load factor for either table then we pass
the resize function in the amount which will be the capacity which will be capacity
is going square the capacity and it will allocate two larger tables, a table 1 and table 2.
suggesting given is that create two local pointers that point to the old tables and have table one table 2
point to two larger tables and then set items two  to zero capacity to new capacity and 
we need to go thorugh every element of your old table one by one and just insert these into the 
new and bigger table. if you set your instance variable table 1 and table 2 to a new sorted tables and 
you assign items one and items two to zero, you can call the insert function within the resize. SO as long as you set your instance variables accordingly.
you can just iterate through each of these one by one and you can just call the insert function pass 
and pass the name and value of an obkject we call insert function. 
size_t x = 


*/