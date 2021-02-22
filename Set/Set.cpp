#include "Set.h"
#include "SetITerator.h"

// Theta(1);
Set::Set() : hashTableCapacity(1), numberElements(0)
{
	hashTable = new TElem[hashTableCapacity];
	hashTable[0] = NULL_TELEM;
}

// Theta(1);
bool Set::add(TElem elem) {
	if (!search(elem))
	{
		resize();
		hashTable[numberElements++] = elem;

		return true;
	}
	return false;
}

// Theta(n) - n = number of elements int the set;
bool Set::remove(TElem elem) {
	if (search(elem))
	{
		int i = 0;
		while (hashTable[i] != elem)
			i++;

		while (i < numberElements - 1)
		{
			hashTable[i] = hashTable[i + 1];
			i++;
		}
		hashTable[i] = NULL_TELEM;

		numberElements--;
		resize();

		return true;
	}
	return false;
}

// Theta(n) - n = number of elements in the set;
bool Set::search(TElem elem) const {
	for (int i = 0; i < hashTableCapacity; i++)
		if (hashTable[i] == elem)
			return true;

	return false;
}

// Theta(1);
int Set::size() const {
	return numberElements;
}

// Theta(1);
bool Set::isEmpty() const {
	if (numberElements == 0)
		return true;
	return false;
}

// Theta(1);
Set::~Set() {
	delete[] hashTable;
}

// Theta(1);
SetIterator Set::iterator() const {
	return SetIterator(*this);
}

// Theta(n) - n = number of elements in the set;
void Set::resize(){
	TElem* new_hashTable;

	// resize double capacity;
	if (numberElements == hashTableCapacity)
	{
		new_hashTable = new TElem[hashTableCapacity * 2];
		for (int i = 0; i < hashTableCapacity; i++)
			new_hashTable[i] = hashTable[i];
		for (int i = hashTableCapacity; i < hashTableCapacity * 2; i++)
			new_hashTable[i] = NULL_TELEM;

		delete[] hashTable;

		hashTable = new_hashTable;
		hashTableCapacity *= 2;
	}
	// resize half capacity;
	else if (numberElements == float(hashTableCapacity) / 2)
	{
		new_hashTable = new TElem[hashTableCapacity / 2];
		for (int i = 0; i < hashTableCapacity / 2; i++)
			new_hashTable[i] = hashTable[i];

		delete[] hashTable;

		hashTable = new_hashTable;
		hashTableCapacity /= 2;
	}
}


