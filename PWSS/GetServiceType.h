#ifndef GETSERVICETYPE_H
#define GETSERVICETYPE_H

#include "State.h"


class GetServiceType : public State
{
	using State::State;
	virtual void Enter() override;
	virtual void Tick() override;
	virtual void Exit() override;
};

#endif
