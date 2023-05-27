#pragma once
#include "State.h"

class GameOverScreen;

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

