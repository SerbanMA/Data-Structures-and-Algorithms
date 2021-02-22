#include "MultiMap.h"
#include "MultiMapIterator.h"
#include <exception>
#include <iostream>

using namespace std;

// The BC = WC = AC = Theta(m). 
// The overall complexity of the resize() method is Theta(m).
void MultiMap::resize()
{
	std::vector<TEl> values;

	for (int i = 0; i < this->m_capacity; i++)
		for (auto elem : this->hashTable[i].second)
		{
			TEl current(this->hashTable[i].first, elem);
			values.push_back(current);
		}

	this->hashTable = new TElem[this->m_capacity * 2];
	this->m_capacity *= 2;
	this->m_size = 0;
	for (int i = 0; i < this->m_capacity; i++)
		this->hashTable[i].first = NULL_TKEY;

	for (auto elem : values)
		this->add(elem.first, elem.second);
}


// The BC = WC = AC = Theta(1). The complexity of the MultiMap() method is Theta(1).
MultiMap::MultiMap()
{
	this->m_capacity = 100;
	this->m_size = 0;
	this->hashTable = new TElem[this->m_capacity];

	for (int i = 0; i < this->m_capacity; i++)
		this->hashTable[i].first = NULL_TKEY;
}

// The BC = AC = Theta(1), WC = Theta(m). 
//The overall complexity of the add(TKey c, TValue v) method is O(m) (amortized O(1)).
void MultiMap::add(TKey c, TValue v) 
{
	int i = 0;
	int pos = this->hash(c, i);

	while (i < this->m_capacity && (this->hashTable[pos].first != NULL_TKEY && this->hashTable[pos].first != DELETED))
	{
		if (this->hashTable[pos].first == c)
		{
			this->hashTable[pos].second.push_back(v);
			this->m_size++;
			return;
		}
		i++;
		pos = this->hash(c, i);
	}

	if (i == this->m_capacity)
	{
		this->resize();
		this->add(c, v);
	}
	else
	{
		this->hashTable[pos].first = c;
		this->hashTable[pos].second.push_back(v);
		this->m_size++;
	}
}

// The BC = AC = Theta(1), WC = Theta(m). 
//The overall complexity of the remove(TKey c, TValue v) method is O(m) (amortized O(1)).
bool MultiMap::remove(TKey c, TValue v) 
{
	int i = 0;
	int pos = this->hash(c, i);

	while (i < this->m_capacity && this->hashTable[pos].first != NULL_TKEY)
	{
		if (this->hashTable[pos].first == c)
		{
			for (int j = 0; j < this->hashTable[pos].second.size(); j++)
				if (this->hashTable[pos].second[j] == v)
				{
					this->hashTable[pos].second.erase(this->hashTable[pos].second.begin() + j);
					this->m_size--;

					if (this->hashTable[pos].second.size() == 0)
						this->hashTable[pos].first = DELETED;
					return true;
				}	
			return false;
		}
		i++;
		pos = this->hash(c, i);
	}
	return  false;
}

// The BC = AC = Theta(1), WC = Theta(m). 
//The overall complexity of the search(TKey c, TValue v) method is O(m) (amortized O(1)).
vector<TValue> MultiMap::search(TKey c) 
{
	int i = 0;
	int pos = this->hash(c, i);

	while (i < this->m_capacity && this->hashTable[pos].first != NULL_TKEY)
	{
		if (this->hashTable[pos].first == c)
			return this->hashTable[pos].second;
		
		i++;
		pos = this->hash(c, i);
	}
	std::vector<TValue> empty;
	return empty;
}

// The BC = WC = AC = Theta(1). 
// The overall complexity of the size() method is Theta(1).
int MultiMap::size() const {
	return this->m_size;
}

// The BC = WC = AC = Theta(m). 
// The overall complexity of the maxKey() method is Theta(m).
TKey MultiMap::maxKey() const
{
	MultiMapIterator it = this->iterator();
	TKey maxKey = 0;

	while (it.valid())
	{
		if (it.getCurrent().first > maxKey)
			maxKey = it.getCurrent().first;
		it.next();
	}

	return maxKey;
}

// The BC = WC = AC = Theta(1). 
// The overall complexity of the isEmpty() method is Theta(1).
bool MultiMap::isEmpty() const {
	return this->m_size == 0;
}

// The BC = WC = AC = Theta(1).
// The overall complexity of the iterator() method is Theta(1).
MultiMapIterator MultiMap::iterator() const {
	return MultiMapIterator(*this);
}

// The BC = WC = AC = Theta(m). 
// The overall complexity of the ~MultiMap() method is Theta(m).
MultiMap::~MultiMap() {
	delete[] this->hashTable;
}

