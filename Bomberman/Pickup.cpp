#include "Pickup.h"
#include "TransformComponent.h"

Pickup::Pickup(glm::vec2 position) : GameObject("Pickup")
{
	isPickedUp = false;
	AddComponent(std::make_unique<TransformComponent>(position, 0.0f));
}

Pickup::~Pickup()
{
}
