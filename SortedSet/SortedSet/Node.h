#pragma once

typedef int TElem;
typedef TElem TComp;

class Node
{
private:
	TComp value;
	Node* next;
	Node* previous;

public:
	//constructor
	Node() : value(0), next(nullptr), previous(nullptr) {}
	Node(int value) : value(value), next(nullptr), previous(nullptr) {}
	Node(int value, Node* next, Node* previous) : value(value), next(next), previous(previous) {}

	//get value
	//set value
	TComp getValue() { return this->value; }
	void setValue(TComp newValue) { this->value = newValue; }

	//get next
	//set next
	Node* getNext() { return this->next; }
	void setNext(Node* newNext) { this->next = newNext; }

	//get previous
	//set previous
	Node* getPrevious() { return this->previous; }
	void setPrevious(Node* newPrevious) { this->previous = newPrevious; }

};