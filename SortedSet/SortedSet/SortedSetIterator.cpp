#include "SortedSetIterator.h"
#include <exception>

using namespace std;

SortedSetIterator::SortedSetIterator(const SortedSet& m) : set(m)
{
	this->first();
}

// Theta(1)
void SortedSetIterator::first() 
{
	currentNode = set.root;
}

// Theta(1)
void SortedSetIterator::next() 
{
	if (!valid())
		throw exception("");

	currentNode = currentNode->getNext();
}

// Theta(1)
TElem SortedSetIterator::getCurrent()
{
	if (!valid())
		throw exception("");
	return currentNode->getValue();
}

// Theta(1)
bool SortedSetIterator::valid() const 
{
	return currentNode != nullptr;
}

