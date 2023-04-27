#pragma once
#include "Component.h"
#include "glm/gtx/string_cast.hpp"
#include <vector>
#include <memory>

class GameObject
{
protected:
	std::vector<std::unique_ptr<Component>> components;
	std::string tag;
public:
	GameObject(std::string tag = "Default");
	virtual ~GameObject();
	void virtual Update(float deltaTime);
	void AddComponent(std::unique_ptr<Component> component);
	template <typename T>
	T* GetComponent();
	std::string GetTag();
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
