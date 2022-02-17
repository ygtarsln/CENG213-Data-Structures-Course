#include "HashTable.h"

#include <cassert>
#include <iostream>
#include <iomanip>

const int KeyedHashTable::PRIME_LIST[PRIME_TABLE_COUNT] =
{
     2,    3,   5,   7,  11,  13,  17,  19,
     23,  29,  31,  37,  41,  43,  47,  53,
     59,  61,  67,  71,  73,  79,  83,  89,
     97, 101, 103, 107, 109, 113, 127, 131,
    137, 139, 149, 151, 157, 163, 167, 173,
    179, 181, 191, 193, 197, 199, 211, 223,
    227, 229, 233, 239, 241, 251, 257, 263,
    269, 271, 277, 281, 283, 293, 307, 311,
    313, 317, 331, 337, 347, 349, 353, 359,
    367, 373, 379, 383, 389, 397, 401, 409,
    419, 421, 431, 433, 439, 443, 449, 457,
    461, 463, 467, 479, 487, 491, 499, 503,
    509, 521, 523, 541
};

int KeyedHashTable::Hash(const std::string& key) const
{
    int hash = 0, i = 0;
    
    while (i < key.length()){
    	hash += key[i] * PRIME_LIST[i];
    	i++;
	}
	
	hash = hash % tableSize;
	return hash;
}

void KeyedHashTable::ReHash()
{
    int newsize = FindNearestLargerPrime(2 * tableSize), hashcode;
    int oldsize = tableSize;
	HashData* temp = table;
    
	table = new HashData[newsize];
	tableSize = newsize;
    
    for (int i = 0; i < oldsize; i++){
    	
		if (temp[i].key == "" || temp[i].key == _DELETED_) continue;
		
		int j = 1;
		hashcode = Hash(temp[i].key);
		
		while (table[hashcode].key != ""){
			hashcode = (hashcode + 2 * j - 1) % tableSize;
			j++;
		}
		
		table[hashcode] = temp[i];
	}
    
    delete[] temp;
}

int KeyedHashTable::FindNearestLargerPrime(int requestedCapacity)
{
    int i = 0;
    
    while (PRIME_LIST[i] <= requestedCapacity) i++;
    
    return PRIME_LIST[i];
}

KeyedHashTable::KeyedHashTable()
{
    table = new HashData[2];
    tableSize = 2;
    occupiedElementCount = 0;
}

KeyedHashTable::KeyedHashTable(int requestedCapacity)
{
    int size = FindNearestLargerPrime(requestedCapacity);
    
    table = new HashData[size];
    tableSize = size;
    occupiedElementCount = 0;
}

KeyedHashTable::KeyedHashTable(const KeyedHashTable& other)
{
	tableSize = other.tableSize;
    occupiedElementCount = other.occupiedElementCount;
    
    table = new HashData[tableSize];
    
    for (int i = 0; i < tableSize; i++){
    	table[i] = other.table[i];
	}
}

KeyedHashTable& KeyedHashTable::operator=(const KeyedHashTable& other)
{
    if (this != &other){
    	
		delete[] table;
    	
    	tableSize = other.tableSize;
    	occupiedElementCount = other.occupiedElementCount;
    	
    	table = new HashData[tableSize];
    	
    	for (int i = 0; i < tableSize; i++){
    		table[i] = other.table[i];
		}
	}
	
	return *this;
}

KeyedHashTable::~KeyedHashTable()
{
    delete[] table;
}

bool KeyedHashTable::Insert(const std::string& key,
                            const std::vector<int>& intArray)
{
    HashData newitem;
    newitem.key = key;
    newitem.intArray = intArray;
    
    int hashcode = Hash(key), i = 1;
    
    while (table[hashcode].key != "" && table[hashcode].key != _DELETED_){
		
		if (table[hashcode].key == key){
			return false;
		}
		
		hashcode = (hashcode + 2 * i - 1) % tableSize;
		i++;
	}
	
	table[hashcode] = newitem;
	occupiedElementCount++;
	
	if (occupiedElementCount * EXPAND_THRESHOLD >= tableSize){
		ReHash();
	}
	
	return true;
}

bool KeyedHashTable::Remove(const std::string& key)
{
    int hashcode = Hash(key), i = 1;
    
    while (table[hashcode].key != key && table[hashcode].key != ""){
    	hashcode = (hashcode + 2 * i - 1) % tableSize;
    	i++;
	}
	
	if (table[hashcode].key == key){
		
		table[hashcode].key = _DELETED_;
		table[hashcode].intArray.clear();
		occupiedElementCount--;
		
		return true;
	}
	
	else{
		return false;
	}
}

void KeyedHashTable::ClearTable()
{
   for (int i = 0; i < tableSize; i++){
   	
	   table[i].key = "";
	   table[i].intArray.clear();
   }
   
   occupiedElementCount = 0;
}

bool KeyedHashTable::Find(std::vector<int>& valueOut,
                          const std::string& key) const
{
    int hashcode = Hash(key), i = 1;
    
    while (table[hashcode].key != ""){
    	
    	if (table[hashcode].key == key){
    		valueOut = table[hashcode].intArray;
    		return true;
		}
		
		hashcode = (hashcode + 2 * i - 1) % tableSize;
		i++;
	}
	
	return false;
}

void KeyedHashTable::Print() const
{
    // ============================= //
    // This function is implemented  //
    // Do not edit this function !   //
    // ============================= //
    std::cout << "HT:";
    if(occupiedElementCount == 0)
    {
        std::cout << " Empty";
    }
    std::cout << "\n";
    for(int i = 0; i < tableSize; i++)
    {
        if(table[i].key == "") continue;

        std::cout << "[" << std::setw(3) << i << "] ";
        std::cout << "[" << table[i].key << "] ";
        std::cout << "[";
        for(size_t j = 0; j < table[i].intArray.size(); j++)
        {
            std::cout << table[i].intArray[j];
            if((j + 1) != table[i].intArray.size())
                std::cout << ", ";
        }
        std::cout << "]\n";
    }
    std::cout.flush();
}
