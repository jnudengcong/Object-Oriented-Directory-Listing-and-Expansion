#include "SortingOfSize.h"
#include "File.h"
#include <vector>

using namespace std;

/*
vector<File> SortingOfSize::sort(vector<File> prefileVector)
{
	vector<File> fileVector;
	vector<File>::iterator i, j;

	fileVector = prefileVector;
	for (i = fileVector.begin(); i != fileVector.end(); i++)
	{
		for (j = i + 1; j != fileVector.end(); j++)
		{
			if ((i->getFiledata()).size < (j->getFiledata()).size)
			{
				_finddata_t temp;
				temp = i->getFiledata();
				i->setFiledata(j->getFiledata());
				j->setFiledata(temp);
			}
		}
	}

	return fileVector;
}
*/

bool SortingOfSize::compare(vector<File>::iterator i, vector<File>::iterator j)
{
	return i->getFiledata().size < j->getFiledata().size;
}