#pragma once

#include "Subject.h"
#include "Observer.h"

class State;

class StateMachine : public Observer, public Subject
{
private:
	std::unique_ptr<State> currentState;
	bool isRunning;
public:
	StateMachine();

	void SwitchState(std::unique_ptr<State> newState);
	void Update(float deltaTime);
	void OnNotify(Event event) override;
	bool GetIsRunning();
};

