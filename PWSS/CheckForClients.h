#ifndef CHECKFORCLIENTS_H
#define CHECKFORCLIENTS_H

#include "State.h"


class CheckForClients : public State
{
	using State::State;
	virtual void Enter() override;
	virtual void Tick() override;
	virtual void Exit() override;
};

#endif
