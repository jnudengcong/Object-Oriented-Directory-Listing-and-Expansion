#include "Sorting.h"

using namespace std;

vector<File> Sorting::sort(vector<File> prefileVector)
{
	vector<File> fileVector;
	vector<File>::iterator i, j;

	fileVector = prefileVector;
	for (i = fileVector.begin(); i != fileVector.end(); i++)
	{
		for (j = i + 1; j != fileVector.end(); j++)
		{
			if (compare(i, j))
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

bool Sorting::compare(vector<File>::iterator i, vector<File>::iterator j)
{
	return false;
}
