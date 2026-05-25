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



*/
