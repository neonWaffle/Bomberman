#pragma once

#include "Subject.h"
#include "Observer.h"

#include <vector>
#include <queue>
#include <memory>

#include "TGUI/TGUI.hpp"

class GameObject;

class EntityManager : public Subject, public Observer
{
private:
	static EntityManager* instance;

	std::vector<GameObject*> objectsToRemove;
	std::queue<std::unique_ptr<GameObject>> objectsToAdd;
	std::vector<tgui::Widget::Ptr> guiElementsToAdd;
	std::vector<tgui::Widget::Ptr> guiElementsToRemove;
	bool removeAll = false;

	EntityManager() = default;
public:
	std::vector<std::unique_ptr<GameObject>> gameObjects;

	static EntityManager* GetInstance();
	EntityManager(EntityManager&) = delete;
	void operator=(const EntityManager&) = delete;

	void AddGameObject(std::unique_ptr<GameObject> object);
	void AddGUIElement(tgui::Widget::Ptr guiElement);
	void RemoveGameObject(GameObject* object);
	void RemoveAllGameObjects();
	void RemoveGUIElement(tgui::Widget::Ptr guiElement);
	void ClearGameObjects();
	void ClearGUIElements();
	void AddGameObjects();

	void OnNotify(Event event) override;
	void OnNotify(Event event, GameObject& gameObject) override;
};

