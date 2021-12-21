
#include <iostream>
#include "StateMachine.h"
#include "ConfigureServer.h"

using namespace std;

int main()
{
    StateMachine stateMachine;
    ServerData data;

    StateMachine st();

    stateMachine.Init(new ConfigureServer(&stateMachine),&data);
    cout << stateMachine.data->serverSocket;
}
