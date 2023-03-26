#pragma once
#include "GameObject.h"
#include "PickupSpeedBoost.h"
#include "PickupExtraBomb.h"
#include "PickupExplosionIncrease.h"
#include <random>

class BoxTile : public GameObject
{
private:
	bool isDestroyed;
	int pickupChance;
	void DropPickup();
public:
	BoxTile(glm::vec2 position);
	virtual ~BoxTile();
	void GetDestroyed();
};

