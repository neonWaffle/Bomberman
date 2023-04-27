#pragma once
#include "State.h"
#include "MainMenu.h"

class MainMenuState : public State
{
private:
	std::unique_ptr<MainMenu> mainMenu;
public:
	MainMenuState(std::shared_ptr<StateMachine> stateMachine, std::shared_ptr<sf::RenderWindow> window = nullptr);
	void EnterState() override;
	void ExitState() override;
	void OnNotify(Event event) override;
};

