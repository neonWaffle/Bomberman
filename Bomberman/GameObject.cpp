#include "GameObject.h"

GameObject::GameObject(std::string tag)
{
	this->tag = tag;
}

GameObject::~GameObject()
{
}

void GameObject::Update(float deltaTime)
{
}

void GameObject::AddComponent(std::unique_ptr<Component> component)
{
	components.emplace_back(std::move(component));
}

std::string GameObject::GetTag()
{
	return tag;
}
