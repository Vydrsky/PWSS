#include "GetServiceType.h"
#include "Statemachine.h"

using namespace std;
void GetServiceType::Enter()
{
	
	for (auto it = stateMachine->data->socketList.begin(); it != stateMachine->data->socketList.end(); ++it) {
		
		int amountRecieved = 0;
		char buff[1024];
		int dataRecieved = 0;
		recv((*it).fd, buff + dataRecieved, 8, 0);
		do {
			amountRecieved = recv((*it).fd, buff + dataRecieved, 1024, 0);
			dataRecieved += amountRecieved;
		} while (amountRecieved > 0 && dataRecieved > 0);
		stateMachine->data->fileMap[(*it).fd].ReadInput(buff);
		for (size_t i = 0;buff[i]!=0 ; i++)
		{
			cout << buff[i];
		};
	}
}

void GetServiceType::Tick()
{
	
}

void GetServiceType::Exit()
{

}
