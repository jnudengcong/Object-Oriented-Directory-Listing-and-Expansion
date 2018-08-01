#include "File.h"

_finddata_t File::getFiledata()
{
	return this->filedata;
}

void File::setFiledata(_finddata_t filedata)
{
	this->filedata = filedata;
}