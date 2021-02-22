#pragma once
#include "Matrix.h"

//DO NOT CHANGE THIS PART
class MatrixIterator
{
	friend class Matrix;
private:
	const Matrix& matrix;
	MatrixIterator(const Matrix& m);

	int index;

public:
	void first();
	void next();
	TElem getCurrent();
	bool valid() const;
};