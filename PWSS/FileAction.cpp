#include "FileAction.h"


FileAction::FileAction(FILE* _file) {
    file = _file;
}

void FileAction::ReadInput(char input[1024]) {
    int pos;
    bool flag = false;
    for (int i = commandIt,j=0; i < 10; i++,j++) {
        if (input[i] != '\n') {
            command[i] = input[j];
            commandIt++;
        }
        else {
            flag = true;
            break;
        }
    }

    if (flag) {
        std::string commandString = command;
        if (commandString == "UPLOAD") {
            mode = POLLRDNORM;
            bufor = Substring(input, 7);
        }
        else if (commandString == "DOWNLOAD") {
            mode = POLLWRNORM;
            bufor = Substring(input, 9);
        }
        else {
            mode = POLLERR;
        }
    }
}

short FileAction::GetMode() {
    return mode;
}

char* FileAction::GetBuff() {
    return bufor;
}

std::string FileAction::GetCommand() {
    return command;
}

FILE* FileAction::GetFILE() {
    return file;
}

bool FileAction::Find(char input[1024], char _char, int* pos) {
    for (int i = 0; i < 1024; i++) {
        if (input[i] == _char) {
            *pos = i;
            return true;
        }
    }
    return false;
}

char* FileAction::Substring(char input[1024], int start, int end) {
    char* substr;
    substr = (char*)malloc(end - start);
    for (int i = start,j=0; i < end; i++,j++) {
        substr[j] = input[i];
    }
    return substr;
}

char* FileAction::Substring(char input[1024], int start) {
    char* substr;
    substr = (char*)malloc(1024 - start);
    for (int i = start,j = 0; i < 1024; i++,j++) {
        substr[j] = input[i];
    }
    return substr;
}

void FileAction::Open(std::string path,std::string mode) {
    fopen_s(&file, path.c_str(), mode.c_str());
    if (file) {
        isOpen = 1;
    }
}

short FileAction::GetState()
{
    return isOpen;
}

void FileAction::SetRecieved(int ammountRecieved)
{
    this->ammountRecieved = ammountRecieved;
}

int FileAction::GetRecieved()
{
    return ammountRecieved;
}
