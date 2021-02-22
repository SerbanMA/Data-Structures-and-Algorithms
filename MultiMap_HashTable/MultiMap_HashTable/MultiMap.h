#pragma once
#include<vector>
#include<utility>
//DO NOT INCLUDE MultiMapIterator

using namespace std;

//DO NOT CHANGE THIS PART
typedef int TKey;
typedef int TValue;
typedef std::pair<TKey, std::vector<TValue>> TElem;
typedef std::pair<TKey, TValue> TEl;
#define NULL_TKEY -111111
#define NULL_TVALUE -111111
#define NULL_TELEM pair<int,std::vector<TValue>>(-111111, -111111)
#define DELETED -111110
class MultiMapIterator;

class MultiMap
{
	friend class MultiMapIterator;

private:
	
	TElem* hashTable;
	int m_size;
	int m_capacity;
	void resize();

public:
	int hash(int k, int i) { return (hashPrime(k) + i * hashSecond(k)) % this->m_capacity; }
	int hashPrime(int k) { return abs(k) % this->m_capacity; }
	int hashSecond(int k) { return 1 + (abs(k) % (this->m_capacity - 1)); }

	//constructor
	MultiMap();

	//adds a key value pair to the multimap
	void add(TKey c, TValue v);

	//removes a key value pair from the multimap
	//returns true if the pair was removed (if it was in the multimap) and false otherwise
	bool remove(TKey c, TValue v);

	//returns the vector of values associated to a key. If the key is not in the MultiMap, the vector is empty
	vector<TValue> search(TKey c);

	//returns the number of pairs from the multimap
	int size() const;

	// finds and returns the maximum key from the MultiMap
	//if the MultiMap is empty, it returns NULL_TKEY
	TKey maxKey() const;

	//checks whether the multimap is empty
	bool isEmpty() const;

	//returns an iterator for the multimap
	MultiMapIterator iterator() const;

	//descturctor
	~MultiMap();


};

