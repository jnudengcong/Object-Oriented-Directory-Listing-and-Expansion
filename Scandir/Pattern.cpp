#include "Pattern.h"
#include "File.h"
#include "Scandir.h"
#include "SortingOfSize.h"
#include "SortingOfName.h"
#include "SortingOfTime.h"
#include <cstring>
#include <iostream>
#include <fstream>

using namespace std;

Pattern * Pattern::pInstance = NULL;

Pattern::Pattern()
{

}

Pattern* Pattern::getInstance()
{
	if (pInstance == NULL)
		pInstance = new Pattern();

	return pInstance;
}

void Pattern::subMenu()
{
	cout << "���մ�С����������4" << endl;
	cout << "������������������5" << endl;
	cout << "����ʱ������������6" << endl;
	cout << "��Ҫ��������ν��������7" << endl;
	cout << "������һ��˵�������0" << endl;
}

void Pattern::show()
{
	char dirName[200];
	cout << "����Ҫ�鿴Ŀ¼��·�����ԡ�\\��������" << endl;
	cin.getline(dirName, 200);

	string tempStr = dirName;
	if (tempStr[tempStr.size() - 1] != '\\')
	{
		cout << "Ŀ¼���Ϸ�����ע�������Ŀ¼��·��Ӧ�ԡ�\\������������" << endl << endl;
		return;
	}

	Filelist filelist;
	strcat_s(dirName, "*.*");
	Scandir::scanDir(dirName, filelist);
	
	subMenu();

	int getInt;

	while (cin >> getInt)
	{
		getchar();
		switch (getInt)
		{
			case 0:
				return;
			case 4:
			{
				cout << "����С�������£�" << endl;
				Sorting* ss = new SortingOfSize;
				filelist.setFileVector(ss->sort(filelist.getFileVector()));
				filelist.print();
				delete ss;
				break;
			}	
			case 5:
			{
				cout << "�������������£�" << endl;
				Sorting* sn = new SortingOfName;
				filelist.setFileVector(sn->sort(filelist.getFileVector()));
				filelist.print();
				delete sn;
				break;
			}	
			case 6:
			{
				cout << "��ʱ���������£�" << endl;
				Sorting* st = new SortingOfTime;
				filelist.setFileVector(st->sort(filelist.getFileVector()));
				filelist.print();
				delete st;
				break;
			}
			case 7:
			{
				cout << "����������ν�ʣ�" << endl;
				Scandir sc;
				sc.selectFile(filelist);
				if (filelist.getFileVector().size() == 0)
				{
					cout << "��Ŀ¼�²����ڰ�����ν�ʵ��ļ�����" << endl;
					return;
				}
				break;
			}
			default:
				cout << "���������ӦΪ4��5��6��7��0����һ������" << endl;
				break;
		}
		subMenu();
	}

	getchar();
}

void Pattern::logPattern()
{

	cout << "��־ģʽ����������Ҫ������Ŀ¼��,�ԡ�\\����β��" << endl;
	cin.getline(dirPath, 200);

	string tempStr = dirPath;
	if (tempStr[tempStr.size() - 1] != '\\')
	{
		cout << "Ŀ¼���Ϸ�����ע�������Ŀ¼��·��Ӧ�ԡ�\\������������" << endl << endl;
		return;
	}

	traverseAll(dirPath, 1);
	storeIfm();
	
	cout << endl << endl;
}

void Pattern::difPattern()
{
	readIfm();
	cout << "����ģʽ������־�е��ļ���Ϣ��Ƚϣ��������£�Ϊ����˵���޲��죩:" << endl;
	traverseAll(dirPath, 2);
	showdif();
	cout << endl;
}

void Pattern::traverseAll(const char * dir, int flag)
{
	char dirNew[200];
	strcpy_s(dirNew, dir);
	strcat_s(dirNew, "\\*.*");    // ��Ŀ¼�������"\\*.*"���е�һ������

	intptr_t handle;
	_finddata_t findData;

	handle = _findfirst(dirNew, &findData);
	if (handle == -1)        // ����Ƿ�ɹ�
		return;

	do
	{
		if (findData.attrib & _A_SUBDIR)
		{
			if (strcmp(findData.name, ".") == 0 || strcmp(findData.name, "..") == 0)
				continue;

			// ��Ŀ¼�������"\\"����������Ŀ¼��������һ������
			strcpy_s(dirNew, dir);
			strcat_s(dirNew, "\\");
			strcat_s(dirNew, findData.name);

			if (flag == 1)
			{
				logMap.insert(pair<string, _finddata_t>(normolizePath(dirNew), findData));
				traverseAll(dirNew, 1);
			}
			
			if (flag == 2)
			{
				difMap.insert(pair<string, _finddata_t>(normolizePath(dirNew), findData));
				traverseAll(dirNew, 2);
			}
			
		}
		else
		{
			//addcode
			char tempdir[200];
			strcpy_s(tempdir, dirNew);
			strcpy_s(tempdir, dir);
			strcat_s(tempdir, "\\");
			strcat_s(tempdir, findData.name);

			if (flag == 1)
			{
				logMap.insert(pair<string, _finddata_t>(normolizePath(tempdir), findData));
			}
			
			if (flag == 2)
			{
				difMap.insert(pair<string, _finddata_t>(normolizePath(tempdir), findData));
			}
			
		}
	} while (_findnext(handle, &findData) == 0);

	_findclose(handle);    // �ر��������
}

void Pattern::showdif()
{
	map<string, _finddata_t>::iterator log_it, dif_it;
	log_it = logMap.begin();
	dif_it = difMap.begin();

	while (dif_it != difMap.end())
	{
		bool isNew = true;

		log_it = logMap.begin();
		while (log_it != logMap.end())
		{
			if (dif_it->first == log_it->first)
			{
				isNew = false;
				if (fileIsDif(dif_it->second, log_it->second))
				{
					cout << "�仯���ļ���" << dif_it->first << endl;
					showFileDif(dif_it->second, log_it->second);
					cout << endl;
				}
			}

			log_it++;
		}

		if (isNew)
		{
			cout << "�´������ļ���";
			cout << dif_it->first << endl;
		}

		dif_it++;
	}

	for (log_it = logMap.begin(); log_it != logMap.end(); log_it++)
	{
		bool isDelete = true;
		for (dif_it = difMap.begin(); dif_it != difMap.end(); dif_it++)
		{
			if (log_it->first == dif_it->first)
			{
				isDelete = false;
			}
		}

		if (isDelete)
		{
			cout << "ɾ�����ļ���";
			cout << log_it->first << endl;
		}
	}
}

bool Pattern::fileIsDif(_finddata_t file_d, _finddata_t file_l)
{
	if (
		file_d.attrib != file_l.attrib ||
		strcmp(file_d.name, file_l.name) != 0 ||
		file_d.size != file_l.size ||
		file_d.time_access != file_l.time_access ||
		file_d.time_create != file_l.time_create ||
		file_d.time_write != file_l.time_write
		)
	{
		return true;
	}

	return false;
}

void Pattern::showFileDif(_finddata_t file_d, _finddata_t file_l)
{
	if (file_d.attrib != file_l.attrib)
	{
		//cout << file_d.attrib << "\t" << file_l.attrib << endl;
		cout << "��־�и��ļ������Դ��ţ�";
		cout << file_l.attrib;
		cout << "\t";
		cout << "���ڸ��ļ������Դ��ţ�";
		cout << file_d.attrib;
		cout << endl;
	}

/*
	if (strcmp(file_d.name,file_l.name) != 0)
	{
		cout << file_d.name << "\t" << file_l.name << endl;
	}
*/

	if (file_d.size != file_l.size)
	{
		//cout << file_d.size << "\t" << file_l.size << endl;
		cout << "��־�и��ļ��Ĵ�С��";
		cout << file_l.size;
		cout << "\t";
		cout << "���ڸ��ļ��Ĵ�С��";
		cout << file_d.size;
		cout << endl;
	}

	if (file_d.time_create != file_l.time_create)
	{
		//cout << file_d.time_create << "\t" << file_l.time_create << endl;
		cout << "��־�и��ļ��Ĵ���ʱ�䣺";
		Filelist::printTime(file_l.time_create);
		cout << "\t";
		cout << "���ڸ��ļ��Ĵ���ʱ�䣺";
		Filelist::printTime(file_d.time_create);
		cout << endl;
	}

	if (file_d.time_access != file_l.time_access)
	{
		//cout << file_d.time_access << "\t" << file_l.time_access << endl;
		cout << "��־�и��ļ����һ�α����ʵ�ʱ�䣺";
		Filelist::printTime(file_l.time_access);
		cout << "\t";
		cout << "���ڸ��ļ����һ�α����ʵ�ʱ�䣺";
		Filelist::printTime(file_d.time_access);
		cout << endl;
	}

	if (file_d.time_write != file_l.time_write)
	{
		//cout << file_d.time_write << "\t" << file_l.time_write << endl;
		cout << "��־�и��ļ����һ�α�д���ʱ�䣺";
		Filelist::printTime(file_l.time_write);
		cout << "\t";
		cout << "���ڸ��ļ����һ�α�д���ʱ�䣺";
		Filelist::printTime(file_d.time_write);
		cout << endl;
	}
}

void Pattern::storeIfm()
{
	ofstream outfile;
	outfile.open("logMap.txt");
	if (!outfile)
	{
		cout << "����logMap.txt�ļ�ʧ�ܣ�" << endl;
		outfile.close();
		return;
	}

	outfile << dirPath << endl;
	outfile << logMap.size() << endl;

	map<string, _finddata_t>::iterator iter;
	iter = logMap.begin();

	while (iter != logMap.end())
	{
		outfile << iter->first << endl;
		outfile << iter->second.attrib << endl;
		outfile << iter->second.name << endl;
		outfile << iter->second.size << endl;
		outfile << iter->second.time_access << endl;
		outfile << iter->second.time_create << endl;
		outfile << iter->second.time_write << endl;
		iter++;
	}

	outfile.close();
}

void Pattern::readIfm()
{
	ifstream infile;
	infile.open("logMap.txt");
	if (!infile)
	{
		cout << "��logMap.txt�ļ�ʧ�ܣ�" << endl;
		
		return;
	}

	infile.getline(dirPath, 200);
	
	unsigned int map_size;
	infile >> map_size;

	for (unsigned int i = 0; i < map_size; i++)
	{
		string dir_temp;
		infile.get();
		getline(infile, dir_temp);

		_finddata_t filedata_temp;
		unsigned int attrib;
		char name[260];
		_fsize_t size_temp;
		time_t time_access;
		time_t time_create;
		time_t time_write;
		infile >> attrib;
		//infile.getline(name, 260);

		/*string tempStr;
		infile >> tempStr;
		strcpy_s(name, tempStr.c_str());*/
		//infile >> name;
		infile.get();
		infile.getline(name, 260);
		infile >> size_temp >> time_access >> time_create >> time_write;

		filedata_temp.attrib = attrib;
		strcpy_s(filedata_temp.name,name);
		filedata_temp.size = size_temp;
		filedata_temp.time_access = time_access;
		filedata_temp.time_create = time_create;
		filedata_temp.time_write = time_write;

		logMap.insert(pair<string, _finddata_t>(normolizePath(dir_temp), filedata_temp));
	}

	infile.close();
}

void Pattern::showMap(map<string, _finddata_t> theMap)
{
	map<string, _finddata_t>::iterator it;
	it = theMap.begin();
	while (it != theMap.end())
	{
		cout << it->first << "\t" << it->second.size << endl;
		it++;
	}
}

map<string, _finddata_t> Pattern::getLogMap()
{
	return this->logMap;
}

map<string, _finddata_t> Pattern::getDifMap()
{
	return this->difMap;
}

string Pattern::normolizePath(string str)
{
	string fnd = "\\\\";
	string rep = "\\";
	while (str.find(fnd) != string::npos)
	{
		str.replace(str.find(fnd), fnd.length(), rep);
	}

	return str;
}
