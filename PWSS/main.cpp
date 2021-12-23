
#include <iostream>
#include "StateMachine.h"
#include "ConfigureServer.h"
#include "CheckForClients.h"
#include "GetServiceType.h"
#include "ExecuteCommand.h"

using namespace std;

int main()
{
    StateMachine stateMachine;
    ServerData data;
    CheckForClients* checkForClients = new CheckForClients(&stateMachine);
    GetServiceType* getServiceType = new GetServiceType(&stateMachine);
    ExecuteCommand* executeCommand = new ExecuteCommand(&stateMachine);
    stateMachine.Init(new ConfigureServer(&stateMachine),&data);
    while (1) {
        stateMachine.ChangeState(checkForClients);
        stateMachine.Tick();
        stateMachine.ChangeState(getServiceType);
        stateMachine.Tick();
        stateMachine.ChangeState(executeCommand);
        stateMachine.Tick();
    }
    cout << stateMachine.data->serverSocket;
}
