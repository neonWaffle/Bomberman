#include "GameplayState.h"

#include "MainMenuState.h"
#include "GameOverState.h"
#include "TilemapManager.h"
#include "TilemapConfig.h"
#include "EntityManager.h"
#include "GameplayUI.h"
#include "Player.h"
#include "StateMachine.h"

GameplayState::GameplayState(std::shared_ptr<StateMachine> stateMachine, std::shared_ptr<sf::RenderWindow> window) : State(stateMachine, window)
{
	matchDuration = 120.0f;
	matchTimer = 0.0f;
	closeInStartTime = 60.0f;
	this->playerNumber = playerNumber;
}

void GameplayState::EnterState()
{
	int xTiles = std::ceil(TilemapConfig::screenWidth / TilemapConfig::tileSize);
	int yTiles = std::ceil(TilemapConfig::screenHeight / TilemapConfig::tileSize);
	std::array<glm::vec2, 2> playerStartPoints = TilemapManager::GetInstance()->GetStartPoints();
	closeInRate = (matchDuration - closeInStartTime) / (TilemapConfig::xTileNumber * TilemapConfig::yTileNumber);
	closeInTimer = closeInRate; //Want to start spawning EndTiles as soon as the matchTimer reaches the closeInStartTime

	std::vector<Player*> players;
	for (int i = 0; i < 2; i++)
	{
		auto player = std::make_unique<Player>(playerStartPoints[i], i + 1);
		alivePlayerIds.emplace_back(player->GetPlayerId());
		players.emplace_back(player.get());
		EntityManager::GetInstance()->AddGameObject(std::move(player));
	}

	EntityManager::GetInstance()->AddObserver(this);
	gameplayUI = std::make_unique<GameplayUI>(players);
	gameplayUI->Open();

	Notify(Event::START_GAME);
}

void GameplayState::UpdateState(float deltaTime)
{
	matchTimer += deltaTime;
	gameplayUI->UpdateTimer(matchDuration - matchTimer);

	if (matchTimer >= closeInStartTime)
	{
		closeInTimer += deltaTime;
		if (closeInTimer >= closeInRate)
		{
			closeInTimer -= closeInRate;
			TilemapManager::GetInstance()->FillIn();
		}
		if (matchDuration - matchTimer <= 0)
		{
			stateMachine->SwitchState(std::make_unique<GameOverState>(stateMachine, window, alivePlayerIds[0]));
		}
	}

	for (const auto& gameObject : EntityManager::GetInstance()->gameObjects)
	{
		gameObject->Update(deltaTime);
	}
}

void GameplayState::ExitState()
{
	gameplayUI->Close();
	EntityManager::GetInstance()->RemoveObserver(this);
	EntityManager::GetInstance()->RemoveAllGameObjects();
}

void GameplayState::OnNotify(Event event, GameObject& gameObject)
{
	switch (event)
	{
	case Event::PLAYER_DIED:
		auto player = dynamic_cast<Player*>(&gameObject);
		if (player != nullptr)
		{
			alivePlayerIds.erase(std::remove(alivePlayerIds.begin(), alivePlayerIds.end(), player->GetPlayerId()));
			if (alivePlayerIds.size() == 1)
			{
				stateMachine->SwitchState(std::make_unique<GameOverState>(stateMachine, window, alivePlayerIds[0]));
			}
		}
		break;
	}
}
