#include "SortedSet.h"
#include "SortedSetIterator.h"
#include <iostream>

SortedSet::SortedSet(Relation r) {
	this->root = nullptr;
	this->numberOfElements = 0;
	this->relation = r;
}

// O(n) - n = number of elements in the sortedset;
bool SortedSet::add(TComp elem) {
	
	Node* newNode = new Node{ elem };

	// Empty list;
	if (this->root == nullptr)
		this->root = newNode;

	// List with at least 1 node;
	else
	{
		Node* current = this->root;
		while (current != nullptr && this->relation(current->getValue(), newNode->getValue()))
		{
			if (newNode->getValue() == current->getValue())
			{
				delete newNode;
				return false;
			}
			current = current->getNext();
		}

		// Add to end of list;
		if (current == nullptr)
		{
			current = this->root;
			while (current->getNext() != nullptr)
				current = current->getNext();

			current->setNext(newNode);
			newNode->setPrevious(current);
		}
		// Add before current node;
		else
		{
			if (current->getPrevious() != nullptr)
			{
				newNode->setPrevious(current->getPrevious());
				current->getPrevious()->setNext(newNode);
			}
			else
				root = newNode;

			newNode->setNext(current);
			current->setPrevious(newNode);
		}
	}

	this->numberOfElements++;
	return true;
}

// O(n) - n = number of elements in the sortedset;
bool SortedSet::remove(TComp elem) 
{	
	Node* current = this->root;
	while (current != nullptr && elem != current->getValue())
		current = current->getNext();

	// Empty list;
	if (current == nullptr)
		return false;

	// Remove from beggining
	if (current->getPrevious() == nullptr)
	{
		this->root = current->getNext();
		if (this->root != nullptr)
			this->root->setPrevious(nullptr);
		delete current;
	}
	// Remove from end
	else if (current->getNext() == nullptr)
	{
		current->getPrevious()->setNext(nullptr);
		delete current;
	}

	else
	{
		current->getPrevious()->setNext(current->getNext());
		current->getNext()->setPrevious(current->getPrevious());
		delete current;
	}
		
	this->numberOfElements--;
	return true;
}

// O(n) - n = number of elements in the sortedset;
bool SortedSet::search(TElem elem) const
{
	Node* current = this->root;
	while (current != nullptr && elem != current->getValue())
		current = current->getNext();

	if (current != nullptr)
		return true;
	return false;
}

// O(m*n) - m = number of elements from the sortedset | n = number of elements from s (sortedset)
void SortedSet::unity(const SortedSet& s)
{
	SortedSetIterator it = s.iterator();
	int iverif = 0;
	while (it.valid()) {
		this->add(it.getCurrent());
		it.next();
	}
}

// Theta(1)
int SortedSet::size() const {
	return this->numberOfElements;
}

// Theta(1)
bool SortedSet::isEmpty() const {
	return this->numberOfElements == 0;
}

// Theta(1)
SortedSetIterator SortedSet::iterator() const {
	return SortedSetIterator(*this);
}

// O(n) - n = the number of elements from sortedset
SortedSet::~SortedSet() {
	Node* current = this->root;
	while (current != nullptr)
	{
		Node* nextCurrent = current->getNext();

		delete current;
		current = nextCurrent;
	}
}


