#include "GetServiceType.h"
#include "Statemachine.h"

using namespace std;
void GetServiceType::Enter()
{
}

void GetServiceType::Tick()
{
	for (auto it = stateMachine->data->socketList.begin(); it != stateMachine->data->socketList.end(); ++it) {
		if ((*it).fd != stateMachine->data->serverSocket && stateMachine->data->fileMap[(*it).fd].GetMode() == 0) {
			int amountRecieved = 0;
			char buff[1024] = { 0 };
			amountRecieved = recv((*it).fd, buff, 1024, 0);
			stateMachine->data->fileMap[(*it).fd].SetRecieved(amountRecieved);
			stateMachine->data->fileMap[(*it).fd].ReadInput(buff);
			cout << "Komenda: " << stateMachine->data->fileMap[(*it).fd].GetCommand() << endl;
		}
	}

	
}

void GetServiceType::Exit()
{

}
