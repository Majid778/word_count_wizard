#include <iostream>
#include <fstream>
#include <sstream>
#include <time.h>
#include <string>
#include <stdlib.h>
#include <iomanip>
#include <list>
#include <stack>
#include <vector>
#include <iterator>


using namespace std;

class HashNode//Class for hashnode
{
	private:
		string key;
		int value;//This will track how many times the word/key has occured
	public:
		HashNode(string key)
		{
			this->key = key;
			this->value = 1;//How many times the word has been repeated
		}
		string getkey()
		{
			return key;
		}
		int getvalue()
		{
			return value;
		}
		void increment_value()//when the word occures more than one the value is incremented.
		{
			value = value + 1 ;
		}
		friend class HashTable;
};

class HashTable
{
	private:
		friend class HashNode;
		int size;
		int capacity;
		int collisions;	
		int Hashtype;//User chooses what type of hashfunction to use (1,2,3)
		int words;
		int unique_words;
	public:
		list<HashNode> *buckets;
		HashTable(int capacity,int Hashtype);
		unsigned long Selected_hashCode(string key);
		unsigned long hashCode1(string key);
        unsigned long hashCode2(string key);
        unsigned long hashCode3(string key);
		void insert(string key);
		HashNode* search(string key);
		void Hashsearch(unsigned long int hashcode);
		void erase(string key);
		int getSize();
		int count_collisions();
		int count_unique_words();
		int count_words();
		double find_freq(string word);
		~HashTable();
};

HashTable::HashTable(int capacity,int Hashtype)//Constructor
{
	buckets = new list<HashNode>[capacity];
	this->capacity = capacity;
	this->size = 0;
	this->collisions = 0;
	this->Hashtype = Hashtype;
	this->words = 0;
	this->unique_words = 0;
}
HashTable::~HashTable()//Destructor
{
	for(int i=0; i<capacity; i++){buckets[i].clear();}
	delete[] buckets;
}
unsigned long HashTable::Selected_hashCode(string key)//Returns appropriate hashcode type depending on users selection
{
	if(this->Hashtype == 1){return hashCode1(key);}
	if(this->Hashtype == 2){return hashCode2(key);}
	else{return hashCode3(key);}
}
unsigned long HashTable::hashCode1(string key)//Cyclic Shift 
{
	unsigned long hashcode ;
	int size = key.size();
	for (int i = 0; i<size; i++)
	{
        hashcode = (hashcode << 5)|(hashcode>>27);
		hashcode += (unsigned int)key[i];
	}
	hashcode = hashcode % capacity;
	return hashcode;
}
unsigned long HashTable::hashCode2(string key)//Polynomial
{
	unsigned long hashcode;
	int size = key.size();
	for (int i = 0; i<size; i++)
	{
		hashcode += ((unsigned int)key[i])*i*i;
		hashcode += (unsigned int)key[i];
	}
	hashcode = hashcode % capacity;
	return hashcode;	
}
unsigned long HashTable::hashCode3(string key)//Summation
{
	unsigned long hashcode = 0;
	int size = key.size();
	for (int i = 0; i<size; i++)
	{
		hashcode += (unsigned int)key[i];
	}
	hashcode = hashcode % capacity;
	return hashcode;	
}
void HashTable::insert(string key)//Used to insert the words into the hash function
{
	unsigned long int hashcode = Selected_hashCode(key);
    if(buckets[hashcode].empty())//If the bucket is empty
    {
        buckets[hashcode].push_back(HashNode(key));//add the newly created hashNode into the bucket
		words++;
		unique_words++;//Since the Bucket is empty, this is the first time this word has been seen so the unique_words has been incremented
		size++;
    }
    else
    {
		collisions++;//If the bucket is not empty it means a collision has occured
		bool found = false;//Boolean to check if the word is found from iterating through the HashNodes in the buckets
		for(auto it = buckets[hashcode].begin(); it != buckets[hashcode].end(); it++)//Iterating through the HashNode buckets
		{
			if(it->getkey() == key)//Searching for the key/word
			{
				found = true;
				it->increment_value();//Increment the frequency that the word has occured
				words++;
				size++;
			}
		}
		if(found == false)//If the word is not found then make a new HashNode and add it to the bucket
		{
			buckets[hashcode].push_back(HashNode(key));
			words++;
			unique_words++;
			size++;
		}
    }
}
int HashTable::getSize()//Fucntion to return the size of the Hashtable
{
	return this->size;
}

int HashTable::count_collisions()//Fucntion to return the total amount of collisions
{
	return this->collisions;
}
int HashTable::count_unique_words()//Fucntion to return the total amount of unique words
{
	return this->unique_words;
}
int HashTable::count_words()//Fucntion to return the total amount of words
{
	return this->words;
}
double HashTable::find_freq(string word)//Finds the appropriate HashNode and returns the value variable which tracks the amount of times the word has occured
{
	unsigned long int hashcode = Selected_hashCode(word);
	bool found;
	for(HashNode i :buckets[hashcode])//Iterates through the HashNodes searching for the word
	{
		if(i.getkey() == word)
		{
			found = true;
			return i.getvalue();
		}
	}
	if(found == false)//Error when the word is not found
	{
		cout<<"Word not found"<<endl;
	}
	return 0;
}
