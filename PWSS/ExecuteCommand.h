#ifndef EXECUTECOMMAND_H
#define EXECUTECOMMAND_H

#include "State.h"


class ExecuteCommand : public State
{
	using State::State;
	virtual void Enter() override;
	virtual void Tick() override;
	virtual void Exit() override;
};

#endif

