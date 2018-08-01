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
	cout << "按照大小排序请输入4" << endl;
	cout << "按照名称排序请输入5" << endl;
	cout << "按照时间排序请输入6" << endl;
	cout << "需要输入搜索谓词请输入7" << endl;
	cout << "返回上一层菜单请输入0" << endl;
}

void Pattern::show()
{
	char dirName[200];
	cout << "输入要查看目录的路径，以“\\”结束：" << endl;
	cin.getline(dirName, 200);

	string tempStr = dirName;
	if (tempStr[tempStr.size() - 1] != '\\')
	{
		cout << "目录不合法！！注意输入的目录的路径应以“\\”结束！！！" << endl << endl;
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
				cout << "按大小排序如下：" << endl;
				Sorting* ss = new SortingOfSize;
				filelist.setFileVector(ss->sort(filelist.getFileVector()));
				filelist.print();
				delete ss;
				break;
			}	
			case 5:
			{
				cout << "按名称排序如下：" << endl;
				Sorting* sn = new SortingOfName;
				filelist.setFileVector(sn->sort(filelist.getFileVector()));
				filelist.print();
				delete sn;
				break;
			}	
			case 6:
			{
				cout << "按时间排序如下：" << endl;
				Sorting* st = new SortingOfTime;
				filelist.setFileVector(st->sort(filelist.getFileVector()));
				filelist.print();
				delete st;
				break;
			}
			case 7:
			{
				cout << "请输入搜索谓词：" << endl;
				Scandir sc;
				sc.selectFile(filelist);
				if (filelist.getFileVector().size() == 0)
				{
					cout << "该目录下不存在包含该谓词的文件名！" << endl;
					return;
				}
				break;
			}
			default:
				cout << "输入的数字应为4、5、6、7、0其中一个！！" << endl;
				break;
		}
		subMenu();
	}

	getchar();
}

void Pattern::logPattern()
{

	cout << "日志模式，请输入需要遍历的目录树,以“\\”结尾：" << endl;
	cin.getline(dirPath, 200);

	string tempStr = dirPath;
	if (tempStr[tempStr.size() - 1] != '\\')
	{
		cout << "目录不合法！！注意输入的目录的路径应以“\\”结束！！！" << endl << endl;
		return;
	}

	traverseAll(dirPath, 1);
	storeIfm();
	
	cout << endl << endl;
}

void Pattern::difPattern()
{
	readIfm();
	cout << "差异模式，与日志中的文件信息相比较，差异如下（为空则说明无差异）:" << endl;
	traverseAll(dirPath, 2);
	showdif();
	cout << endl;
}

void Pattern::traverseAll(const char * dir, int flag)
{
	char dirNew[200];
	strcpy_s(dirNew, dir);
	strcat_s(dirNew, "\\*.*");    // 在目录后面加上"\\*.*"进行第一次搜索

	intptr_t handle;
	_finddata_t findData;

	handle = _findfirst(dirNew, &findData);
	if (handle == -1)        // 检查是否成功
		return;

	do
	{
		if (findData.attrib & _A_SUBDIR)
		{
			if (strcmp(findData.name, ".") == 0 || strcmp(findData.name, "..") == 0)
				continue;

			// 在目录后面加上"\\"和搜索到的目录名进行下一次搜索
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

	_findclose(handle);    // 关闭搜索句柄
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
					cout << "变化的文件：" << dif_it->first << endl;
					showFileDif(dif_it->second, log_it->second);
					cout << endl;
				}
			}

			log_it++;
		}

		if (isNew)
		{
			cout << "新创建的文件：";
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
			cout << "删除的文件：";
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
		cout << "日志中该文件的属性代号：";
		cout << file_l.attrib;
		cout << "\t";
		cout << "现在该文件的属性代号：";
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
		cout << "日志中该文件的大小：";
		cout << file_l.size;
		cout << "\t";
		cout << "现在该文件的大小：";
		cout << file_d.size;
		cout << endl;
	}

	if (file_d.time_create != file_l.time_create)
	{
		//cout << file_d.time_create << "\t" << file_l.time_create << endl;
		cout << "日志中该文件的创建时间：";
		Filelist::printTime(file_l.time_create);
		cout << "\t";
		cout << "现在该文件的创建时间：";
		Filelist::printTime(file_d.time_create);
		cout << endl;
	}

	if (file_d.time_access != file_l.time_access)
	{
		//cout << file_d.time_access << "\t" << file_l.time_access << endl;
		cout << "日志中该文件最后一次被访问的时间：";
		Filelist::printTime(file_l.time_access);
		cout << "\t";
		cout << "现在该文件最后一次被访问的时间：";
		Filelist::printTime(file_d.time_access);
		cout << endl;
	}

	if (file_d.time_write != file_l.time_write)
	{
		//cout << file_d.time_write << "\t" << file_l.time_write << endl;
		cout << "日志中该文件最后一次被写入的时间：";
		Filelist::printTime(file_l.time_write);
		cout << "\t";
		cout << "现在该文件最后一次被写入的时间：";
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
		cout << "创建logMap.txt文件失败！" << endl;
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
		cout << "打开logMap.txt文件失败！" << endl;
		
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
