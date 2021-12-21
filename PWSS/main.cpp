﻿
#include <iostream>
#include "StateMachine.h"
#include "ConfigureServer.h"
#include "CheckForClients.h"

using namespace std;

int main()
{
    StateMachine stateMachine;
    ServerData data;

    stateMachine.Init(new ConfigureServer(&stateMachine),&data);
    while (1) {
        stateMachine.ChangeState(new CheckForClients(&stateMachine));
        stateMachine.Tick();
    }
    cout << stateMachine.data->serverSocket;
}
