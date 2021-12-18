
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

