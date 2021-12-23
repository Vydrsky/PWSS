#include "ExecuteCommand.h"
#include "Statemachine.h"

void ExecuteCommand::Enter()
{
}

void ExecuteCommand::Tick()
{
	for (auto it = stateMachine->data->socketList.begin();it != stateMachine->data->socketList.end();++it)
	{
		if (stateMachine->data->fileMap[(*it).fd].GetCommand() == "DOWNLOAD") {
			std::string path=stateMachine->data->fileMap[(*it).fd].GetBuff();
			std::cout << path;
			if (!stateMachine->data->fileMap[(*it).fd].GetState()) {
				stateMachine->data->fileMap[(*it).fd].Open(path, "rb");
			}
			char buff[1024];
			if (!feof(stateMachine->data->fileMap[(*it).fd].GetFILE())) {
				int ammountRead=fread(buff, 1, 1024, stateMachine->data->fileMap[(*it).fd].GetFILE());
				sendAll(buff, ammountRead, (*it).fd);
			}
			else {
				closesocket((*it).fd);
				fclose(stateMachine->data->fileMap[(*it).fd].GetFILE());
			}
		}
		else if (stateMachine->data->fileMap[(*it).fd].GetCommand() == "UPLOAD") {
			std::cout << "hello" << std::endl;
			std::string path = "C:\\Users\\Wydrzu\\source\\repos\\PWSS\\Debug\\";
			char ip4[INET_ADDRSTRLEN];
			path.append(ip4);
			path.append(std::to_string((*it).fd));
			char buff[1024];
			std::cout << stateMachine->data->fileMap[(*it).fd].GetState() << std::endl;
			if (!stateMachine->data->fileMap[(*it).fd].GetState()) {
				stateMachine->data->fileMap[(*it).fd].Open(path, "wb");
				std::cout << stateMachine->data->fileMap[(*it).fd].GetState() << std::endl;
			}
			int bytesRecieved;
			do {
				bytesRecieved = recv((*it).fd, buff, sizeof(buff), 0);
				fwrite(buff, sizeof(char), bytesRecieved, stateMachine->data->fileMap[(*it).fd].GetFILE());
			} while (bytesRecieved > 0);

			if (stateMachine->data->fileMap[(*it).fd].GetState()) {
				fclose(stateMachine->data->fileMap[(*it).fd].GetFILE());
			}
		}
	}
}

void ExecuteCommand::Exit()
{
}

int ExecuteCommand::sendAll(char* buff, int size, int socket)
{
	int ammountSent;
	while ((ammountSent = send(socket, buff, size, 0)) < 0) {
		if (ammountSent < size) {
			size -= ammountSent;
			buff += ammountSent;
		}
	}
	std::cout << ammountSent << std::endl;
	return 0;
}
