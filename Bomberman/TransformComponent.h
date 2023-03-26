#pragma once
#include "Component.h"

class TransformComponent : public Component
{
private:
	glm::vec2 position; //Based on graphics subsystem's coordinates
	float rotation;
	glm::vec2 scale;
public:
	TransformComponent(glm::vec2 position, float rotation);
	void SetPosition(glm::vec2 position);
	glm::vec2 GetPosition();
};

