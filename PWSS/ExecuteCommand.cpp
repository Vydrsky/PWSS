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
			if (!stateMachine->data->fileMap[(*it).fd].GetState()) {
				stateMachine->data->fileMap[(*it).fd].Open(path, "rb");
			}
			char buff[1024];
			if (!feof(stateMachine->data->fileMap[(*it).fd].GetFILE())) {
				int ammountRead=fread(buff, 1, 1024, stateMachine->data->fileMap[(*it).fd].GetFILE());
				sendAll(buff, ammountRead, (*it).fd);
			}
			else {
				fclose(stateMachine->data->fileMap[(*it).fd].GetFILE());
				closesocket((*it).fd);
				stateMachine->data->socketList.erase(it--);
				std::cout << "Zamknieto polaczenie: " << (*it).fd << std::endl;
			}
		}
		else if (stateMachine->data->fileMap[(*it).fd].GetCommand() == "UPLOAD") {
			std::string path = "C:\\Users\\Wydrzu\\source\\repos\\PWSS\\Debug\\";
			char ip4[INET_ADDRSTRLEN]; 
			inet_ntop(AF_INET, &(stateMachine->data->clientAddr.sin_addr), ip4, INET_ADDRSTRLEN);
			path.append(ip4);
			path.append(std::to_string((*it).fd));
			char buff[1024];
			if (!stateMachine->data->fileMap[(*it).fd].GetState()) {
				stateMachine->data->fileMap[(*it).fd].Open(path, "wb");
				fwrite(stateMachine->data->fileMap[(*it).fd].GetBuff(), sizeof(char), (stateMachine->data->fileMap[(*it).fd].GetRecieved())-7, stateMachine->data->fileMap[(*it).fd].GetFILE());
			}
			int bytesRecieved=0;
			bytesRecieved = recv((*it).fd, buff, 1024, 0);
			if (bytesRecieved > 0) {
				fwrite(buff, sizeof(char), bytesRecieved, stateMachine->data->fileMap[(*it).fd].GetFILE());
				if (bytesRecieved < 1024) {
					fclose(stateMachine->data->fileMap[(*it).fd].GetFILE());
				}
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
	return 0;
}
