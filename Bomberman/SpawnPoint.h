#pragma once
#include "GameObject.h"

class SpawnPoint : public GameObject
{
public:
	SpawnPoint(glm::vec2 pos, int playerId);
};

