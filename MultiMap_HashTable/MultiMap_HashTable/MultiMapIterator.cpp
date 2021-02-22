#include "MultiMapIterator.h"
#include "MultiMap.h"


// The BC = AC = Theta(1), WC = Theta(m). 
// The overall complexity of the MultiMapIterator(const MultiMap & c) method is O(m).
MultiMapIterator::MultiMapIterator(const MultiMap& m): m(m) {
	this->first();
}

// The BC = WC = AC = Theta(1). 
// The overall complexity of the getCurrent() method is Theta(1).
TEl MultiMapIterator::getCurrent() const
{
	TEl current;
	current.first = this->m.hashTable[this->indexKey].first;
	current.second = this->m.hashTable[this->indexKey].second[indexValue];
	return current;
}

// The BC = WC = AC = Theta(1). 
// The overall complexity of the valid() method is Theta(1).
bool MultiMapIterator::valid() const {
	
	if (this->indexKey == -1 || this->indexKey == this->m.m_capacity)
		return false;
	return true;
}

// The BC = AC = Theta(1), WC = Theta(m). 
// The overall complexity of the next() method is O(m).
void MultiMapIterator::next() 
{
	int iKey = this->indexKey;
	int iValue = this->indexValue + 1;

	if (iValue < this->m.hashTable[iKey].second.size())
	{
		this->indexValue++;
		return;
	}
	else
	{
		iKey++;
		while (iKey < this->m.m_capacity)
		{
			if (this->m.hashTable[iKey].first != NULL_TKEY && this->m.hashTable[iKey].first != DELETED)
			{
				this->indexKey = iKey;
				this->indexValue = 0;
				return;
			}
			iKey++;
		}
	}

	this->indexKey = this->m.m_capacity;
}

// The BC = AC = Theta(1), WC = Theta(m). 
// The overall complexity of the first() method is Theta(m).
void MultiMapIterator::first() 
{
	int i = 0;

	while (i < this->m.m_capacity)
	{
		if (this->m.hashTable[i].first != NULL_TKEY && this->m.hashTable[i].first != DELETED)
		{
			this->indexKey = i;
			this->indexValue = 0;
			return;
		}
		i++;
	}
}

