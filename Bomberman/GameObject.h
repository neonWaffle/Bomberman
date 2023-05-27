#pragma once
#include "Component.h"

#include <vector>
#include <memory>

#include "glm/gtx/string_cast.hpp"

class GameObject
{
protected:
	std::vector<std::unique_ptr<Component>> components;
	std::string tag;
public:
	GameObject(const std::string& tag = "Default");
	virtual ~GameObject();

	void virtual Update(float deltaTime);
	std::string GetTag();

	void AddComponent(std::unique_ptr<Component> component);
	template <typename T>
	T* GetComponent();
};

template<typename T>
inline T* GameObject::GetComponent()
{
	for (int i = 0; i < components.size(); i++)
	{
		T* component = dynamic_cast<T*>(components[i].get());
		if (component != nullptr)
			return component;
	}
	return nullptr;
}
