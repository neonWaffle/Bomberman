#include "BackgroundTile.h"

#include "TransformComponent.h"
#include "GraphicsComponent.h"

BackgroundTile::BackgroundTile(glm::vec2 position, int size) : GameObject()
{
	AddComponent(std::move(std::make_unique<TransformComponent>(position, 0.0f)));
	AddComponent(std::move(std::make_unique<GraphicsComponent>("Assets/Sprites/Environment/background.png", 1, 1, size, size)));
}