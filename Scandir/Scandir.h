#ifndef GUARD_Scandir_h
#define GUARD_Scandir_h

#include "Filelist.h"
#include <string>

using namespace std;

class Scandir
{
private:
	string selectCriteria;
public:
	void static scanDir(const char * dir, Filelist& filelist);
	void selectFile(Filelist& filelist);
	bool includeCriteria(char name[260]);
};

#endif