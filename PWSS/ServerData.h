#include <winsock2.h>
#include <vector>
class ServerData {
public:
	int serverSocket;
	sockaddr_in serverAddr;
	std::vector<pollfd> socketList;
	std::vector<pollfd>::iterator it;
};

