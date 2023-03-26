#pragma once
#include "Pickup.h"

class PickupSpeedBoost : public Pickup
{
private:
	float boostAmount;
public:
	PickupSpeedBoost(glm::vec2 position);
	virtual ~PickupSpeedBoost();
	void GetPickedUp(Player& player) override;
};

