#include "State.h"

#include "StateMachine.h"

State::State(std::shared_ptr<StateMachine> stateMachine, std::shared_ptr<sf::RenderWindow> window)
{
	this->stateMachine = stateMachine;
	this->window = window;
}

void State::EnterState()
{
}

void State::UpdateState(float deltaTime)
{
}

void State::ExitState()
{
}
