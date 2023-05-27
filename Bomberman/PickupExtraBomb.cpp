#include "PickupExtraBomb.h"

#include "PhysicsComponent.h"
#include "GraphicsComponent.h"
#include "EntityManager.h"
#include "TilemapConfig.h"
#include "Player.h"

PickupExtraBomb::PickupExtraBomb(glm::vec2 position) : Pickup(position)
{
	AddComponent(std::make_unique<PhysicsComponent>(true, glm::vec2(TilemapConfig::tileSize * 0.5f, TilemapConfig::tileSize * 0.5f), true));
	AddComponent(std::make_unique<GraphicsComponent>("Assets/Sprites/Objects/pickupExtraBomb.png", 1, 1, TilemapConfig::tileSize, TilemapConfig::tileSize));
}

PickupExtraBomb::~PickupExtraBomb()
{
}

void PickupExtraBomb::GetPickedUp(Player& player)
{
	if (!isPickedUp)
	{
		player.IncreaseBombAmount();
		EntityManager::GetInstance()->RemoveGameObject(this);
	}
}
