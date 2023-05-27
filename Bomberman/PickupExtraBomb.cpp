#include "PickupExtraBomb.h"

#include "PhysicsComponent.h"
#include "GraphicsComponent.h"
#include "EntityManager.h"

PickupExtraBomb::PickupExtraBomb(glm::vec2 position) : Pickup(position)
{
	int size = 48;
	AddComponent(std::make_unique<PhysicsComponent>(true, glm::vec2(size * 0.5f, size * 0.5f), true));
	AddComponent(std::make_unique<GraphicsComponent>("Assets/Sprites/Objects/pickupExtraBomb.png", 1, 1, size, size));
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
