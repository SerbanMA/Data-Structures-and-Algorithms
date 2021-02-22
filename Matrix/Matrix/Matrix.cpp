#include "Matrix.h"
#include "MatrixIterator.h"
#include <exception>

using namespace std;

Matrix::Matrix(int nrLines, int nrCols) 
{
	this->head = NULL_POS;
	this->lines = nrLines;
	this->columns = nrCols;

	int capacity = nrLines * nrCols;
	
	this->elements = new TElem[capacity];
	for (int i = 0; i < capacity; i++)
		this->elements[i] = NULL_TELEM;

	this->next = new int[nrLines * nrCols];
	for (int i = 0; i < capacity; i++)
		this->next[i] = NULL_POS;
}


// Theta(1)
int Matrix::nrLines() const 
{
	return this->lines;
}

// Theta(1)
int Matrix::nrColumns() const 
{
	return this->columns;
}

// Theta(1)
TElem Matrix::element(int i, int j) const {
	
	if (i < 0 || i >= this->lines || j < 0 || j >= this->columns)
		throw exception();

	return this->elements[i * this->columns + j];
}

// O(n) - n = number of the elements in the matrix (AC=WC=BC)
TElem Matrix::modify(int i, int j, TElem e) {
	if (i < 0 || i >= this->lines || j < 0 || j >= this->columns)
		throw exception();

	int position = i * this->columns + j;
	TElem preValue= this->elements[position];

	if (e == NULL_TELEM && preValue == NULL_TELEM)
	{
		return NULL_TELEM;
	}
	// Element exist!
	else if (preValue != NULL_TELEM) 
	{
		// Modify element;
		if (e != NULL_TELEM) 
			this->elements[position] = e;

		// Remove element;
		else // (e == NULL_TELEM)
		{
			// Remove front
			if (this->head == position) 
			{
				this->head = this->next[position];

				this->elements[position] = e;
				this->next[position] = NULL_POS;
			}

			else
			{
				int prevPosition = 0;
				int nextPosition = this->head;

				while (nextPosition != NULL_POS && nextPosition < position)
				{
					prevPosition = nextPosition;
					nextPosition = this->next[nextPosition];
				}
				nextPosition = this->next[nextPosition];

				// Remove end
				if (nextPosition == NULL_POS) 
				{
					this->elements[position] = e;
					next[prevPosition] = NULL_POS;
				}
				// Remove between
				else 
				{
					this->elements[position] = e;
					next[prevPosition] = nextPosition;
				}
			}
		}
	}
	// Element doesn't exist!
	else
	{
		// Add front
		if (position < this->head || this->head == NULL_POS) 
		{
			this->elements[position] = e;
			this->next[position] = this->head;
			this->head = position;
		}

		else
		{
			int prevPosition = 0;
			int nextPosition = this->head;

			while (nextPosition != NULL_POS && nextPosition < position)
			{
				prevPosition = nextPosition;
				nextPosition = this->next[nextPosition];
			}

			// Add end
			if (nextPosition == NULL_POS) 
			{
				this->elements[position] = e;
				next[prevPosition] = position;
			}
			// Add between
			else 
			{
				this->elements[position] = e;
				next[prevPosition] = position;
				next[position] = nextPosition;
			}
		}
	}

	return preValue;
}

// Theta(1)
MatrixIterator Matrix::iterator() const
{
	return MatrixIterator(*this);
}
