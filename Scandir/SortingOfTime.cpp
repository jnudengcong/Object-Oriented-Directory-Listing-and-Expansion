#include "SortingOfTime.h"
#include "File.h"
#include <time.h>
#include <vector>

using namespace std;

/*
vector<File> SortingOfTime::sort(vector<File> prefileVector)
{
	vector<File> fileVector;
	vector<File>::iterator i, j;

	fileVector = prefileVector;
	for (i = fileVector.begin(); i != fileVector.end(); i++)
	{
		for (j = i + 1; j != fileVector.end(); j++)
		{
			if (
				compareTime
				(
				(i->getFiledata()).time_write, (j->getFiledata()).time_write
				)
				)
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

bool SortingOfTime::compare(vector<File>::iterator i, vector<File>::iterator j)
{
	return compareTime(i->getFiledata().time_write, j->getFiledata().time_write);
}

bool SortingOfTime::compareTime(time_t tl, time_t tr)
{
	bool isLessThan = false;
	struct tm tml, tmr;
	localtime_s(&tml, &tl);
	localtime_s(&tmr, &tr);

	if (tml.tm_year < tmr.tm_year)
	{
		isLessThan = true;
	}
	else if (tml.tm_year == tmr.tm_year)
	{
		if (tml.tm_mon < tmr.tm_mon)
		{
			isLessThan = true;
		}
		else if (tml.tm_mon == tmr.tm_mon)
		{
			if (tml.tm_mday < tmr.tm_mday)
			{
				isLessThan = true;
			}
			else if (tml.tm_mday == tmr.tm_mday)
			{
				if (tml.tm_hour < tmr.tm_hour)
				{
					isLessThan = true;
				}
				else if (tml.tm_hour == tmr.tm_hour)
				{
					if (tml.tm_min < tmr.tm_min)
					{
						isLessThan = true;
					}
					else if (tml.tm_min == tmr.tm_min)
					{

					}
					else {}
				}
				else {}
			}
			else {}
		}
		else {}
	}
	else {}

	return isLessThan;
}
