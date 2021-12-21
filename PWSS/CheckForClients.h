#ifndef CHECKFORCLIENTS_H
#define CHECKFORCLIENTS_H

#include "State.h"
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

class CheckForClients : public State
{
	using State::State;
	virtual void Enter() override;
	virtual void Tick() override;
	virtual void Exit() override;
};

#endif
