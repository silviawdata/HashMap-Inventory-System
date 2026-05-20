/*
 * Name: Silvia Williams
 * Description: This program implements a hash map using 
 * double hashing. It stores key/value pairs and supports insert, 
 * update, find, and getValue functions.
 * Input: Data from main.cpp
 * Output: Values are  returned to main.cpp
 *
 */

#include "hashMap.h"
#include <cstdlib>
#include <string>
// #include <cmath>
using std::size_t;
using std::string;

//////  HASH MAP CONSTRUCTOR FUNCTION  /////////
// initializes hash map with given capacity
// sets items1 and items2 to 0;
// allocates table1 and table 2
// then using a for loop to set all entries
// to nullptr
template <class t1, class t2>
hashMap<t1, t2>::hashMap(size_t initCapacity)
{
    capacity = initCapacity;
    items1 = 0;
    items2 = 0;

    table1 = new node *[capacity];
    table2 = new node *[capacity];
    for (size_t i = 0; i < capacity; i++)
    {
        table1[i] = nullptr;
        table2[i] = nullptr;
    }
}

/////  HASH MAP DESTRUCTOR FUNCTION  ///////////
// deallocates memory for hash map
// traverses through table1 and table2
// deletes each node if it exists
// then deletes both tables 
// to avoid mememory leaks. 
template <class t1, class t2>
hashMap<t1, t2>::~hashMap()
{
    for (size_t i = 0; i < capacity; i++)
    {
        if (table1[i] != nullptr)
        {
            delete table1[i];
        }
        table1[i] = nullptr;
    }

    for (size_t i = 0; i < capacity; i++)
    {
        if (table2[i] != nullptr)
        {
            delete table2[i];
        }
        table2[i] = nullptr;
    }
    delete[] table1;
    delete[] table2;
}
////////   HASH 1 FUNCTION   /////////////////////////////
// 1st hash function given a string, calculates hash value
// by summing each character increasing powers of 10
// so that position of characters affects the result
// and helps reduce collisons. 
// Processes string from left to right.
template <class t1, class t2>
size_t hashMap<t1, t2>::hash1(string k)
{

    size_t result = 0, power = 1, len = k.size();

    for (size_t i = 0; i < len; i++)
    {
        //static cast converts character to it's ASCII value number
        result = result + static_cast<size_t>(k[i]) * power;
        power = power * 10;
    }
    return result;
}
//////// HASH 2 FUNCTION ///////////////////////////
// similar logic as the 1st hash function but 
// processes string right to left.
template <class t1, class t2>
size_t hashMap<t1, t2>::hash2(string k)
{

    //i-1 to adjusts index to match correct string position
    size_t result = 0, power = 1, len = k.size();

    for (size_t i = len; i > 0; i--)
    {

        result = result + static_cast<size_t>(k[i - 1]) * power;
        power = power * 10;
    }
    return result;
}

////  RESIZE FUNCTION  //////////////////////////////////
// resizes hash map when map load factor gets too large
// stores old table1 and table2 in local pointers
// allocates two larger tables with updated capacity
// resets counters and reinserts old elements
template <class t1, class t2>
void hashMap<t1, t2>::resize(size_t amount)
{
    //store old tables
    node **oldTable1 = table1;
    node **oldTable2 = table2;

    //store old capacity
    size_t oldCap = capacity;

    //update capacity and allocate new tables
    capacity = capacity * amount;
    table1 = new node *[capacity];
    table2 = new node *[capacity];

    for (size_t i = 0; i < capacity; i++)
    {

        table1[i] = nullptr;
        table2[i] = nullptr;
    }

    //reset item counters for new tables
    items2 = 0;
    items1 = 0;

    //reinserts old elements into new tables
    for (size_t i = 0; i < oldCap; i++)
    {

        if (oldTable1[i] != nullptr)
        {

            insert(oldTable1[i]->key, oldTable1[i]->value);
            delete oldTable1[i];
        }

        if (oldTable2[i] != nullptr)
        {

            insert(oldTable2[i]->key, oldTable2[i]->value);
            delete oldTable2[i];
        }
    }

    //delets old tables after use. 
    delete[] oldTable2;
    delete[] oldTable1;
}

//////////   LOOK UP FUNCTION   //////////////////////////
// calculates index using double hashing technique
// checks table1 and table2 at calculated index
// returns index if slot is empty or key is found
// increments collison counter i if collision occurs. 
template <class t1, class t2>
size_t hashMap<t1, t2>::lookup(t1 k)
{
    size_t i = 0;

    while (true)
    {
        //calculates where to look in the table using 
        // double hashing formula. 
        size_t index = (hash1(k) + i * hash2(k)) % capacity;

        //returns index if key is found or if an empty slot is available
        if (table1[index] == nullptr)
        {
            return index;
        }
        if (table1[index]->key == k)
        {
            return index;
        }
        if (table2[index] == nullptr)
        {
            return index;
        }
        if (table2[index]->key == k)
        {
            return index;
        }

        i++;
    }
}

//////////  FIND FUNCTION  ////////////////////////
// checks if a key exists in the hash map 
// uses lookup function to find index
// and returns true if key is found in table1 or table2
// otherwise returns false
template <class t1, class t2>
bool hashMap<t1, t2>::find(t1 k)
{
    size_t index = lookup(k);

    if (table1[index] != nullptr && table1[index]->key == k)
    {
        return true;
    }

    if (table2[index] != nullptr && table2[index]->key == k)
    {
        return true;
    }
    return false;
}
/////////  INSERT FUNCTION  ///////////////////////////////////
// inserts a new key/value pair into hash map
// resizes if load factor is too high
// uses look up function to find index
// and does not insert duplicate keys
template <class t1, class t2>
void hashMap<t1, t2>::insert(t1 k, t2 v)
{
    // calculates load factor of hash map
    // total items divided by capacity
    double loadFactor = static_cast<double>(items1 + items2);
    loadFactor = loadFactor / static_cast<double>(capacity);

    // if load factor reaches 20%, resize the table 
    // doubles the capacity of the hash map
    if (loadFactor >= 0.2)
    {

        resize(2);
    }

    //calls lookup function and stores in index
    size_t index = lookup(k);

    //if key already exists, do not insert
    // otherwise insert into first available table
    // update item counter for the table used
    if (table1[index] != nullptr && table1[index]->key == k)
    {

        return;
    }

    if (table2[index] != nullptr && table2[index]->key == k)
    {

        return;
    }

    if (table1[index] == nullptr)
    {

        table1[index] = new node(k, v);

        items1++;
    }
    else if (table2[index] == nullptr)
    {

        table2[index] = new node(k, v);
        items2++;
    }
}

//// UPDATE FUNCTION ////////////////////////////////////
// updates value for an existing key
// uses look up function to find index
// if key is not found, inserts new key/value pair
template <class t1, class t2>
void hashMap<t1, t2>::update(t1 k, t2 v)
{
    size_t index = lookup(k);
    if (table1[index] != nullptr && table1[index]->key == k)
    {

        table1[index]->value = v;
    }
    else if (table2[index] != nullptr && table2[index]->key == k)
    {

        table2[index]->value = v;
    }
    else
    {
        insert(k, v);
    }
}

/////////  GET VALUE FUNCTION  /////////////////////////
// returns value for given key
// uses lookup function to find index
// returns default value if key not found
template <class t1, class t2>
t2 hashMap<t1, t2>::getValue(t1 k)
{
    size_t index = lookup(k);
    if (table1[index] != nullptr && table1[index]->key == k)
    {
        return table1[index]->value;
    }

    if (table2[index] != nullptr && table2[index]->key == k)
    {
        return table2[index]->value;
    }

    return t2();
}

template class hashMap<string, int>;
template class hashMap<string, string>;
template class hashMap<string, bool>;
template class hashMap<string, menuType>;
