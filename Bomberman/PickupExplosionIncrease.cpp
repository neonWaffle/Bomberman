#include "PickupExplosionIncrease.h"

#include "PhysicsComponent.h"
#include "GraphicsComponent.h"
#include "EntityManager.h"

PickupExplosionIncrease::PickupExplosionIncrease(glm::vec2 position) : Pickup(position)
{
	int size = 48;
	AddComponent(std::make_unique<PhysicsComponent>(true, glm::vec2(size * 0.5f, size * 0.5f), true));
	AddComponent(std::make_unique<GraphicsComponent>("Assets/Sprites/Objects/pickupExplosionIncrease.png", 1, 1, size, size));
}

PickupExplosionIncrease::~PickupExplosionIncrease()
{
}

void PickupExplosionIncrease::GetPickedUp(Player& player)
{
	if (!isPickedUp)
	{
		player.IncreaseBombStrength();
		EntityManager::GetInstance()->RemoveGameObject(this);
	}
}
