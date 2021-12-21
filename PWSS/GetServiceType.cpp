#include "GetServiceType.h"
#include "Statemachine.h"

using namespace std;
void GetServiceType::Enter()
{
	
	for (auto it = stateMachine->data->socketList.begin(); it != stateMachine->data->socketList.end(); ++it) {
		char bufor[1024] = "UPLOAD\nabcdsgd";
		stateMachine->data->fileMap[(*it).fd].ReadInput(bufor);
	}
}

void GetServiceType::Tick()
{
	
}

void GetServiceType::Exit()
{

}
