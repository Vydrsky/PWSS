#include "FileAction.h"


FileAction::FileAction() {

}

FileAction::FileAction(FILE* f) {
	file = f;
	buff = "";
	data = "";
	mode = -1;
}


void FileAction::WriteToBuff(std::string str) {
	buff = str;
}

void FileAction::CheckMode() {
	if (size_t pos=buff.find("\n") != std::string::npos) {
		if (buff.substr(0, 6) == "UPLOAD") {
			mode = POLLRDNORM;
			data = buff.substr(pos);
		}
		else if (buff.substr(0, 7) == "DOWNLOAD") {
			mode = POLLWRNORM;
			data = buff.substr(pos);
		}
		else {
			mode = POLLERR;
		}
	}
}

FILE* FileAction::GetFile() {
	return file;
}

int FileAction::GetMode() {
	return mode;
}

std::string FileAction::GetPath() {
	return data;
}