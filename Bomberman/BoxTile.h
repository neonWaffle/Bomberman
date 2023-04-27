#pragma once
#include "GameObject.h"

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

