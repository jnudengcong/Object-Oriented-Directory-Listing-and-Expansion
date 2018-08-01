#ifndef GUARD_Filelist_h
#define GUARD_Filelist_h

#include "File.h"
#include <vector>

using namespace std;

class Filelist
{
private:
	vector<File> fileVector;

public:
	void setFileVector(vector<File> fileVector);
	vector<File> getFileVector();
	void push_back(File file);
	void print();
	void static printTime(time_t time);
};

#endif
