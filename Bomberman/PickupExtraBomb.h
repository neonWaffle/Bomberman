#pragma once

#include "Pickup.h"

class Player;

class PickupExtraBomb : public Pickup
{
public:
	PickupExtraBomb(glm::vec2 position);
	virtual ~PickupExtraBomb();

	void GetPickedUp(Player& player) override;
};

