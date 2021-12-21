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
    int commandIt = 0;
    char command[10] = {};
    char* bufor = {};
    char* data = {};
    short mode = 0;
public:
    FileAction() {};
    FileAction(FILE* _file);
    void ReadInput(char input[1024]);
    short GetMode();
    std::string GetBuff();
    FILE* GetFILE();
    std::string GetCommand();
    bool Find(char input[1024], char _char, int* pos);
    char* Substring(char input[1024], int start, int end);
    char* Substring(char input[1024], int start);


};

#endif

