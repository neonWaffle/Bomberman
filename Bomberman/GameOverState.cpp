#include "GameOverState.h"
#include "GameplayState.h"
#include "MainMenuState.h"
#include "TilemapManager.h"

GameOverState::GameOverState(std::shared_ptr<StateMachine> stateMachine, std::shared_ptr<sf::RenderWindow> window, int winnerId) : State(stateMachine, window)
{
	gameOverScreen = std::make_unique<GameOverScreen>();
	this->winnerId = winnerId;
}

void GameOverState::EnterState()
{
	gameOverScreen->Open(winnerId);
	gameOverScreen->AddObserver(this);
	TilemapManager::GetInstance()->AddObserver(this);
	Notify(Event::PLAYER_DIED);
}

void GameOverState::ExitState()
{
	gameOverScreen->Close();
	gameOverScreen->RemoveObserver(this);
	TilemapManager::GetInstance()->RemoveObserver(this);
}

void GameOverState::OnNotify(Event event)
{
	switch (event)
	{
	case Event::OPEN_MAIN_MENU:
		stateMachine->SwitchState(std::make_unique<MainMenuState>(stateMachine, window));
		break;
	case Event::START_GAME:
		stateMachine->SwitchState(std::make_unique<GameplayState>(stateMachine, window));
		break;
	case Event::EXIT_GAME:
		Notify(Event::EXIT_GAME);
		break;
	}
}
