#include "MatrixIterator.h"
#include <exception>

using namespace std;

// Theta(1)
MatrixIterator::MatrixIterator(const Matrix& m) : matrix(m)
{
	this->index = matrix.head;
}

// Theta(1)
void MatrixIterator::first()
{
	this->index = matrix.head;
}

// Theta(1)
void MatrixIterator::next()
{
	if (!valid())
		throw exception("");
	this->index = matrix.next[this->index];
}

// Theta(1)
TElem MatrixIterator::getCurrent()
{
	if (!valid())
		throw exception("");
	return matrix.elements[this->index];
}

// Theta(1)
bool MatrixIterator::valid() const
{
	int capacity = matrix.lines * matrix.columns;
	if (this->index < 0 || this->index >= capacity)
		return false;
	return true;
}

