#ifndef GUARD_SortingOfTime_h
#define GUARD_SortingOfTime_h

#include "Sorting.h"
#include "File.h"
#include <vector>

using namespace std;

class SortingOfTime : public Sorting
{
protected:
	//vector<File> sort(vector<File> prefileVector);
	virtual bool compare(vector<File>::iterator i, vector<File>::iterator j);
	bool compareTime(time_t tl, time_t tr);
};

#endif