#include "Scandir.h"
#include <io.h>
#include <iostream>
#include <string>

using namespace std;

void Scandir::scanDir(const char * dirName, Filelist& filelist)
{
	intptr_t handle;
	_finddata_t finddata;
	File file;

	handle = _findfirst(dirName, &finddata);
	if (handle == -1)
	{
		cout << "打开第一个文件失败！" << endl;
		return;
	}

	do
	{
		if (finddata.attrib & _A_SUBDIR
			&& strcmp(finddata.name, ".") == 0
			&& strcmp(finddata.name, "..") == 0)
		{
			file.setFiledata(finddata);
			filelist.push_back(file);
		}
		else
		{
			file.setFiledata(finddata);
			filelist.push_back(file);
		}
	} while (_findnext(handle, &finddata) == 0);

	_findclose(handle);
}

void Scandir::selectFile(Filelist& filelist)
{
	cin >> selectCriteria;
	vector<File> newFilelist = filelist.getFileVector();
	for (vector<File>::iterator i = newFilelist.begin(); i < newFilelist.end();)
	{
		if (!includeCriteria(i->getFiledata().name))
			i = newFilelist.erase(i);
		else
			i++;
	}
	filelist.setFileVector(newFilelist);
}

bool Scandir::includeCriteria(char name[260])
{
	string temp = name;
	if (temp.find(selectCriteria) == string::npos)
		return false;

	return true;
}