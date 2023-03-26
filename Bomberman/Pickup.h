#pragma once
#include "GameObject.h"
#include "Player.h"

class Pickup : public GameObject
{
protected:
	bool isPickedUp;
public:
	Pickup(glm::vec2 position);
	virtual ~Pickup();
	virtual void GetPickedUp(Player& player) = 0;
};

