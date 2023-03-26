#include "FloorTile.h"

FloorTile::FloorTile(glm::vec2 position) : GameObject()
{
	AddComponent(std::move(std::make_unique<TransformComponent>(position, 0.0f)));
	AddComponent(std::move(std::make_unique<GraphicsComponent>("Assets/Sprites/Environment/floorTile.png", 1, 1, TilemapConfig::tileSize, TilemapConfig::tileSize)));
}