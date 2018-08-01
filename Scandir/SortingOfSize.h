#ifndef GUARD_SortingOfSize_h
#define GUARD_SortingOfSize_h

#include "Sorting.h"
#include "File.h"
#include <vector>

using namespace std;

class SortingOfSize : public Sorting
{
protected:
	//vector<File> sort(vector<File> prefileVector);
	virtual bool compare(vector<File>::iterator i, vector<File>::iterator j);
};

#endif