#include "EndTile.h"

#include "TransformComponent.h"
#include "PhysicsComponent.h"
#include "GraphicsComponent.h"
#include "TilemapConfig.h"

EndTile::EndTile(glm::vec2 position) : GameObject("EndTile")
{
	AddComponent(std::move(std::make_unique<TransformComponent>(position, 0.0f)));
	AddComponent(std::move(std::make_unique<PhysicsComponent>(false, glm::vec2(TilemapConfig::tileSize * 0.5f, TilemapConfig::tileSize * 0.5f))));
	AddComponent(std::move(std::make_unique<GraphicsComponent>("Assets/Sprites/Environment/endTile.png", 1, 1, TilemapConfig::tileSize, TilemapConfig::tileSize)));
}
