#include "PickupSpeedBoost.h"
#include "PhysicsComponent.h"
#include "GraphicsComponent.h"
#include "EntityManager.h"

PickupSpeedBoost::PickupSpeedBoost(glm::vec2 position) : Pickup(position)
{
	int size = 48;
	boostAmount = 1.5f;
	AddComponent(std::make_unique<PhysicsComponent>(true, glm::vec2(size * 0.5f, size * 0.5f), true));
	AddComponent(std::make_unique<GraphicsComponent>("Assets/Sprites/Objects/pickupSpeedBoost.png", 1, 1, size, size));
}

PickupSpeedBoost::~PickupSpeedBoost()
{
}

void PickupSpeedBoost::GetPickedUp(Player& player)
{
	if (!isPickedUp)
	{
		player.IncreaseSpeed(boostAmount);
		EntityManager::GetInstance()->RemoveGameObject(this);
	}
}
