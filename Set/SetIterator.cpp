#include "SetIterator.h"
#include "Set.h"

#include <stdexcept>


// Theta(1)
SetIterator::SetIterator(const Set& m) : set(m), currentIndex(0)
{
	if (set.numberElements == 0)
		currentIndex = set.hashTableCapacity;
}

// Theta(1)
void SetIterator::first() 
{
	currentIndex = 0;
}

// Theta(1)
void SetIterator::next() 
{
	if (!valid())
		throw std::runtime_error("");
	currentIndex++;
}

// Theta(1)
void SetIterator::previous()
{
	if (!valid())
		throw std::runtime_error("");
	currentIndex--;
}

// Theta(1)
TElem SetIterator::getCurrent()
{
	if (!valid())
		throw std::runtime_error("");
	return set.hashTable[currentIndex];
}

// Theta(1)
bool SetIterator::valid() const 
{
	if (0 <= currentIndex && currentIndex < set.numberElements)
		return true;
	return false;
}



