#pragma once
#include "SortedMap.h"
#include <stack>

//DO NOT CHANGE THIS PART
class SMIterator{
	friend class SortedMap;
private:
	SortedMap& map;
	SMIterator(SortedMap& m);

	Node* currentNode;
	std::stack<Node*> stack;

public:
	void first();
	void next();
	bool valid() const;
    TElem getCurrent() const;
};

