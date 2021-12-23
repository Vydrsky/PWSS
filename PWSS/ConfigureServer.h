#ifndef CONFIGURESERVER_H
#define CONFIGURESERVER_H

#include "State.h"


class ConfigureServer : public State
{
public:
	//c++11 uzywanie konstruktora bazowego
	using State::State;
	virtual void Enter() override;
	virtual void Tick() override;
	virtual void Exit() override;
};

#endif

