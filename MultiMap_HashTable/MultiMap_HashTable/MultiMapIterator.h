#pragma once
#include "MultiMap.h"

class MultiMap;

class MultiMapIterator
{
	friend class MultiMap;

private:
	const MultiMap& m;
	int indexKey = -1;
	int indexValue;

	MultiMapIterator(const MultiMap& m);

public:
	TEl getCurrent()const;
	bool valid() const;
	void next();
	void first();
};

