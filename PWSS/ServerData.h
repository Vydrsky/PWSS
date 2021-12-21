#ifndef SERVERDATA_H
#define SERVERDATA_H

#include <winsock2.h>
#include <vector>
#include <map>
#include "FileAction.h"

class ServerData {
public:
	int serverSocket;
	sockaddr_in serverAddr;
	std::vector<pollfd> socketList;
	std::vector<pollfd>::iterator it;
	sockaddr_in clientAddr;
	std::map<SOCKET, FileAction> fileMap;
};
#endif

