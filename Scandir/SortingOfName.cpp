#include "SortingOfName.h"
#include "File.h"
#include <vector>

using namespace std;

/*
vector<File> SortingOfName::sort(vector<File> prefileVector)
{
	vector<File> fileVector;
	vector<File>::iterator i, j;

	fileVector = prefileVector;
	for (i = fileVector.begin(); i != fileVector.end(); i++)
	{
		for (j = i + 1; j != fileVector.end(); j++)
		{
			if ((i->getFiledata()).name[0] < (j->getFiledata()).name[0])
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

bool SortingOfName::compare(vector<File>::iterator i, vector<File>::iterator j)
{
	

	string iStr = i->getFiledata().name;
	string jStr = j->getFiledata().name;

	unsigned int min = iStr.size();

	if (jStr.size() < min)
		min = jStr.size();

	for (unsigned int i = 0; i < min; i++)
	{
		if (iStr[i] < jStr[i])
		{
			return false;
		}
		else if (iStr[i] > jStr[i])
		{
			return true;
		}
		else
		{
			continue;
		}
	}

	return true;
}