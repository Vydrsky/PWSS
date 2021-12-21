
#include <iostream>
#include "StateMachine.h"
#include "ConfigureServer.h"
#include "CheckForClients.h"
#include "GetServiceType.h"

using namespace std;

int main()
{
    StateMachine stateMachine;
    ServerData data;

    stateMachine.Init(new ConfigureServer(&stateMachine),&data);
    FileAction fileAction;
    char buf[1024] = "UPLOAD\nGFDSHdfghbjfgdhbagfdhbjhjdfaghjdfg";
    fileAction.ReadInput(buf);
    cout << fileAction.GetCommand() << endl;
    cout << fileAction.GetBuff() << endl;
    while (1) {
        stateMachine.ChangeState(new CheckForClients(&stateMachine));
        stateMachine.Tick();
    }
    cout << stateMachine.data->serverSocket;
}
