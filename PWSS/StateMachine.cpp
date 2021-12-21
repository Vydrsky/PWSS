#include "StateMachine.h"
#include "State.h"

void StateMachine::Init(State* initState,ServerData* d) {
	data = d;
	state = initState;
	state->Enter();
}

void StateMachine::ChangeState(State* newState) {
	state->Exit();
	state = newState;
	state->Enter();
}

void StateMachine::Tick() {
	state->Tick();
}

void StateMachine::Kill() {
	state->Exit();
	state = NULL;
	free(this);
	exit(1);
}