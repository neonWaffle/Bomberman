#pragma once
#include "State.h"
#include "GameplayState.h"
#include "MainMenuState.h"
#include "GameOverScreen.h"

class GameOverState : public State
{
private:
	std::unique_ptr<GameOverScreen> gameOverScreen;
	int winnerId;
public:
	GameOverState(std::shared_ptr<StateMachine> stateMachine, std::shared_ptr<sf::RenderWindow> window, int winnerId);
	void EnterState() override;
	void ExitState() override;
	void OnNotify(Event event) override;
};

