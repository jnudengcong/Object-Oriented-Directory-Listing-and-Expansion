#ifndef GUARD_File_h
#define GUARD_File_h

#include <io.h>

class File
{
private:
	_finddata_t filedata;

public:
	_finddata_t getFiledata();
	void setFiledata(_finddata_t filedata);
};

#endif