#include "SpawnPoint.h"

#include "TransformComponent.h"
#include "GraphicsComponent.h"
#include "TilemapConfig.h"

SpawnPoint::SpawnPoint(glm::vec2 pos, int playerId)
{
	AddComponent(std::move(std::make_unique<TransformComponent>(pos, 0.0f)));
	std::string iconPath = playerId == 1 ? "Assets/Sprites/UI/playerOneIcon.png" : "Assets/Sprites/UI/playerTwoIcon.png";
	AddComponent(std::move(std::make_unique<GraphicsComponent>(iconPath, 1, 1, TilemapConfig::tileSize, TilemapConfig::tileSize)));
}
