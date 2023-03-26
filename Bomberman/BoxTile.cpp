#include "BoxTile.h"

BoxTile::BoxTile(glm::vec2 position) : GameObject("BoxTile")
{
	AddComponent(std::move(std::make_unique<TransformComponent>(position, 0.0f)));
	AddComponent(std::move(std::make_unique<PhysicsComponent>(false, glm::vec2(TilemapConfig::tileSize * 0.5f, TilemapConfig::tileSize * 0.5f))));
	AddComponent(std::move(std::make_unique<GraphicsComponent>("Assets/Sprites/Environment/box.png", 1, 1, TilemapConfig::tileSize, TilemapConfig::tileSize)));
	isDestroyed = false;
	pickupChance = 30;
}

BoxTile::~BoxTile()
{
}

void BoxTile::GetDestroyed()
{
	if (!isDestroyed)
	{
		isDestroyed = true;
		DropPickup();
		EntityManager::GetInstance()->RemoveGameObject(this);
	}
}

void BoxTile::DropPickup()
{
	std::random_device random;
	std::uniform_int_distribution<int> distribution(0, 100);
	std::mt19937 engine(random());
	int chance = distribution(engine);

	if (chance >= 100 - pickupChance)
	{
		distribution = std::uniform_int_distribution(0, 2);
		int pickup = distribution(engine);
		switch (pickup)
		{
		case 0:
			EntityManager::GetInstance()->AddGameObject(std::make_unique<PickupSpeedBoost>(GetComponent<TransformComponent>()->GetPosition()));
			break;
		case 1:
			EntityManager::GetInstance()->AddGameObject(std::make_unique<PickupExplosionIncrease>(GetComponent<TransformComponent>()->GetPosition()));
			break;
		case 2:
			EntityManager::GetInstance()->AddGameObject(std::make_unique<PickupExtraBomb>(GetComponent<TransformComponent>()->GetPosition()));
			break;
		}
	}
}
