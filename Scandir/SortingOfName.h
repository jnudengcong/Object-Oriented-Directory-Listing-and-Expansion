#ifndef GUARD_SortingOfName_h
#define GUARD_SortingOfName_h

#include "Sorting.h"
#include "File.h"
#include <vector>

using namespace std;

class SortingOfName : public Sorting
{
protected:
	//vector<File> sort(vector<File> prefileVector);
	virtual bool compare(vector<File>::iterator i, vector<File>::iterator j);
};

#endif
