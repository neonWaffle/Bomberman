#include "Explosion.h"

Explosion::Explosion(glm::vec2 position) : GameObject("Explosion")
{
	timer = 0.0f;
	duration = 1.0f;
	isOver = false;
	AddComponent(std::move(std::make_unique<TransformComponent>(position, 0.0f)));
	AddComponent(std::move(std::make_unique<PhysicsComponent>(true, glm::vec2(TilemapConfig::tileSize * 0.45f, TilemapConfig::tileSize * 0.45f), true)));
	AddComponent(std::move(std::make_unique<GraphicsComponent>("Assets/Sprites/Objects/bombExplosion.png", 8, 1, TilemapConfig::tileSize, TilemapConfig::tileSize)));
	auto* graphicsComponent = GetComponent<GraphicsComponent>();
	auto animation = std::make_unique<Animation>("Assets/Sprites/Objects/bombExplosion.png", 8, 1, TilemapConfig::tileSize, TilemapConfig::tileSize, duration, false);
	graphicsComponent->AddAnimation("Explode", std::move(animation));
	graphicsComponent->SwitchAnimation("Explode");
}

void Explosion::Update(float deltaTime)
{
	timer += deltaTime;
	if (timer >= duration && !isOver)
	{
		isOver = true;
		EntityManager::GetInstance()->RemoveGameObject(this);
	}
}
