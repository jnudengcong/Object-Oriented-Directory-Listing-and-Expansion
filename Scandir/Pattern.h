#ifndef GUARD_Pattern_h
#define GUARD_Pattern_h

#include <map>
#include "File.h"

using namespace std;

class Pattern
{
private:
	map<string, _finddata_t> logMap;
	map<string, _finddata_t> difMap;
	char dirPath[200];
	static Pattern * pInstance;
	Pattern();

public:
	void subMenu();
	void show();
	void logPattern();
	void difPattern();
	void traverseAll(const char * dir, int flag);
	void showdif();
	void storeIfm();
	void readIfm();
	void showMap(map<string, _finddata_t>);
	map<string, _finddata_t> getLogMap();
	map<string, _finddata_t> getDifMap();
	string normolizePath(string);
	void showFileDif(_finddata_t, _finddata_t);
	bool fileIsDif(_finddata_t, _finddata_t);
	static Pattern* getInstance();
};



#endif