#ifndef STATE_H
#define STATE_H

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

