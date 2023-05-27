#include "PickupSpeedBoost.h"

#include "PhysicsComponent.h"
#include "GraphicsComponent.h"
#include "EntityManager.h"
#include "TilemapConfig.h"
#include "Player.h"

PickupSpeedBoost::PickupSpeedBoost(glm::vec2 position) : Pickup(position)
{
	boostAmount = 1.5f;
	AddComponent(std::make_unique<PhysicsComponent>(true, glm::vec2(TilemapConfig::tileSize * 0.5f, TilemapConfig::tileSize * 0.5f), true));
	AddComponent(std::make_unique<GraphicsComponent>("Assets/Sprites/Objects/pickupSpeedBoost.png", 1, 1, TilemapConfig::tileSize, TilemapConfig::tileSize));
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
