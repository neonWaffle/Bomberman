#pragma once
#include "GameObject.h"

class Explosion : public GameObject
{
private:
	float duration;
	float timer;
	bool isOver;
public:
	Explosion(glm::vec2 position);
	void Update(float deltaTime) override;
};

