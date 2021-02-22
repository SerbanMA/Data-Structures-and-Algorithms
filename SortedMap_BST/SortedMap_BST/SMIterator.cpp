#include "SMIterator.h"
#include "SortedMap.h"
#include <exception>

using namespace std;

//Theta(1);
SMIterator::SMIterator(SortedMap& m) : map(m), currentNode{ nullptr }, stack{ std::stack<Node*>{} }
{
	this->first();
}


//O(n);
void SMIterator::first()
{
	currentNode = map.root;
	stack = std::stack<Node*>{};
	while (currentNode != nullptr)
	{
		stack.push(currentNode);
		currentNode = currentNode->left;
	}

	if (!stack.empty())
		currentNode = stack.top();
	else
		currentNode = nullptr;
}

//BC = O(log(n)) AC = O(log(n)) WC = O(n)
void SMIterator::next()
{
	if (!this->valid())
		throw std::exception("");

	Node* node = stack.top();
	stack.pop();

	if (node->right != nullptr)
	{
		node = node->right;
		while (node != nullptr)
		{
			stack.push(node);
			node = node->left;
		}
	}

	if (!stack.empty())
		currentNode = stack.top();
	else
		currentNode = nullptr;
}

//Theta(1)
bool SMIterator::valid() const
{
	return currentNode != nullptr;
}

//Theta(1)
TElem SMIterator::getCurrent() const
{
	if (!this->valid())
		throw std::exception("");

	return currentNode->info;
}


