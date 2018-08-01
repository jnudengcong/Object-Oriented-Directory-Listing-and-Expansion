#include "Filelist.h"
#include <iostream>
#include <iomanip>
#include <time.h>

using namespace std;

void Filelist::setFileVector(vector<File> fileVector)
{
	this->fileVector = fileVector;
}

vector<File> Filelist::getFileVector()
{
	return this->fileVector;
}

void Filelist::push_back(File file)
{
	vector<File> fileVector;
	fileVector = this->getFileVector();
	fileVector.push_back(file);
	this->setFileVector(fileVector);
}

void Filelist::print()
{
	vector<File> fileVector;
	vector<File>::iterator i;

	fileVector = this->getFileVector();

	cout << "文件名" << "\t\t\t\t"
		 << "大小(bytes)" << "\t"
		 << "最后一次被写入的时间" << endl;

	for (i = fileVector.begin(); i != fileVector.end(); i++)
	{
		_finddata_t filedata;
		filedata = i->getFiledata();
		if (strcmp(filedata.name, ".") != 0 && strcmp(filedata.name, ".."))
		{
			cout << setiosflags(ios::left) << setw(30)
				<< filedata.name << "\t" << setw(15) << filedata.size << "\t";
			printTime(filedata.time_write);
			cout << endl;
		}
	}

	cout << endl;
}

void Filelist::printTime(time_t time)
{
	struct tm t;
	localtime_s(&t, &time);
	printf("%d/%.2d/%.2d %.2d:%.2d", t.tm_year + 1900, t.tm_mon + 1, t.tm_mday, t.tm_hour, t.tm_min);
}