#ifndef SERVERDATA_H
#define SERVERDATA_H

#include <winsock2.h>
#include <ws2tcpip.h>
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
	socklen_t clientLen;
	std::map<SOCKET, FileAction> fileMap;

};
#endif

