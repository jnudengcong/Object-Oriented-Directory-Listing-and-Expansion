#ifndef GUARD_Sorting_h
#define GUARD_Sorting_h

#include "File.h"
#include <vector>

using namespace std;

class Sorting
{
public:
	vector<File> sort(vector<File> prefileVector);
protected:
	virtual bool compare(vector<File>::iterator i, vector<File>::iterator j);
};

#endif 

