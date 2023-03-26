#include "StateMachine.h"

StateMachine::StateMachine()
{
}

void StateMachine::SwitchState(std::unique_ptr<State> newState)
{
	if (currentState != nullptr)
	{
		currentState->RemoveObserver(this);
		currentState->ExitState();
	}
	currentState = std::move(newState);
	currentState->AddObserver(this);
	currentState->EnterState();
}

void StateMachine::Update(float deltaTime)
{
	if (currentState != nullptr)
		currentState->UpdateState(deltaTime);
}

void StateMachine::OnNotify(Event event)
{
	Notify(event); //Used to notify subsystems of the events
	switch (event)
	{
	case Event::EXIT_GAME:
		isRunning = false;
		break;
	}
}

bool StateMachine::GetIsRunning()
{
	return isRunning;
}
