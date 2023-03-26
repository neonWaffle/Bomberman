#pragma once
#include "Pickup.h"

class PickupExplosionIncrease : public Pickup
{
public:
	PickupExplosionIncrease(glm::vec2 position);
	virtual ~PickupExplosionIncrease();
	void GetPickedUp(Player& player) override;
};

