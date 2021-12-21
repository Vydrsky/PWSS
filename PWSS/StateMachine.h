#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include <stdio.h>
#include "ServerData.h"

class State;

class StateMachine
{
private:
	State* state;
public:
	ServerData* data;
	void Init(State* initState,ServerData* d);
	void ChangeState(State* newState);
	void Tick();
	void Kill();
};

#endif

