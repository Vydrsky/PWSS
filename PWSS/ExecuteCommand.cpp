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
			//sendAll(,,(*it).fd);
		}
		else if (stateMachine->data->fileMap[(*it).fd].GetCommand() == "UPLOAD") {

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
