#ifndef FILEACTION_H
#define FILEACTION_H
#include <stdio.h>
#include <string>
#include <iostream>
#include <winsock2.h>
class FileAction
{
private:
	FILE* file;
	std::string buff;
	std::string data;
	int mode;

public:
	FileAction();
	FileAction(FILE* f);
	FILE* GetFile();
	int GetMode();
	void WriteToBuff(std::string str);
	void CheckMode();
	std::string GetPath();
};

#endif

