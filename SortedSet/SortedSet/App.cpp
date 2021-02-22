#include "ShortTest.h"
#include "ExtendedTest.h"
#include "SortedSet.h"
#include "SortedSetIterator.h"
#include <iostream>
//
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
//

using namespace std;

int main() {
	testAll();
	testAllExtended();

	cout << "Test end" << endl;
	//
	_CrtDumpMemoryLeaks();
	//
	system("pause");
}