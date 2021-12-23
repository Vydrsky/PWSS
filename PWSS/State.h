#ifndef STATE_H
#define STATE_H

#include "FileAction.h"
#include <iostream>
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#include <winsock2.h>
#include <stdio.h>
#include <fstream>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#include <string>
#include <vector>
#include <map>
#pragma comment(lib, "ws2_32.lib")

class StateMachine;

class State
{
public:
	StateMachine* stateMachine;
	State(StateMachine* fsm);
	virtual void Enter() {};
	virtual void Tick() {};
	virtual void Exit() {};
};

#endif

