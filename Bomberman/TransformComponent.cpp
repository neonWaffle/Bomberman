#include "TransformComponent.h"

TransformComponent::TransformComponent(glm::vec2 position, float rotation)
{
	this->position = position;
	this->rotation = rotation;
}

void TransformComponent::SetPosition(glm::vec2 position)
{
	this->position = position;
}

glm::vec2 TransformComponent::GetPosition()
{
	return position;
}
