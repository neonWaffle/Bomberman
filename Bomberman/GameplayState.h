#pragma once
#include "State.h"
#include "MainMenuState.h"
#include "GameOverState.h"
#include "TilemapManager.h"
#include "GameplayUI.h"

class GameplayState : public State
{
private:
	std::unique_ptr<GameplayUI> gameplayUI;
	std::vector<int> alivePlayerIds;
	float matchDuration;
	float matchTimer;
	float closeInStartTime;
	float closeInTimer;
	float closeInRate;
	bool isClosingIn;
	int playerNumber;
public:
	GameplayState(std::shared_ptr<StateMachine> stateMachine, std::shared_ptr<sf::RenderWindow> window);
	void EnterState() override;
	void UpdateState(float deltaTime) override;
	void ExitState() override;
	void OnNotify(Event event, GameObject& gameObject) override;
};

