#pragma once
#include "Pickup.h"
#include "Player.h"

class PickupExtraBomb : public Pickup
{
public:
	PickupExtraBomb(glm::vec2 position);
	virtual ~PickupExtraBomb();
	void GetPickedUp(Player& player) override;
};

