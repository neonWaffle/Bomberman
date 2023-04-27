#pragma once
#include "Observer.h"
#include "Subject.h"
#include "StateMachine.h"
#include <SFML/Graphics.hpp>
#include <memory>

class StateMachine;

class State : public Observer, public Subject
{
protected:
	std::shared_ptr<sf::RenderWindow> window;
	std::shared_ptr<StateMachine> stateMachine;
public:
	State(std::shared_ptr<StateMachine> stateMachine, std::shared_ptr<sf::RenderWindow> window);
	virtual void EnterState();
	virtual void UpdateState(float deltaTime);
	virtual void ExitState();
};

