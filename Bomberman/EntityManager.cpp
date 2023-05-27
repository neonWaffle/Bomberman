#include "EntityManager.h"

#include "GameObject.h"

EntityManager* EntityManager::instance;

void EntityManager::AddGameObject(std::unique_ptr<GameObject> object)
{
	auto subject = dynamic_cast<Subject*>(object.get());
	if (subject != nullptr)
	{
		subject->AddObserver(this);
	}
	objectsToAdd.push(std::move(object));
}

void EntityManager::AddGUIElement(tgui::Widget::Ptr guiElement)
{
	guiElementsToAdd.emplace_back(guiElement);
}

void EntityManager::RemoveGameObject(GameObject* object)
{
 	auto subject = dynamic_cast<Subject*>(object);
	if (subject != nullptr)
	{
		subject->RemoveObserver(this);
	}
	objectsToRemove.emplace_back(object);
}

void EntityManager::RemoveAllGameObjects()
{
	removeAll = true;
}

void EntityManager::RemoveGUIElement(tgui::Widget::Ptr guiElement)
{
	guiElementsToRemove.emplace_back(guiElement);
}

void EntityManager::ClearGameObjects()
{
	if (removeAll)
	{
		for (int i = gameObjects.size() - 1; i >= 0; i--)
		{
			//Used to notify the subsystems to do any cleanups related to removal of a game object
			Notify(Event::GAME_OBJECT_REMOVED, *gameObjects[i]);
			gameObjects.erase(std::remove(gameObjects.begin(), gameObjects.end(), gameObjects[i]));
		}
		objectsToRemove.clear();
		removeAll = false;
		return;
	}

	for (int i = 0; i < objectsToRemove.size(); i++)
	{
		for (int j = 0; j < gameObjects.size(); j++)
		{
			if (objectsToRemove[i] == gameObjects[j].get())
			{	
				//Used to notify the subsystems to do any cleanups related to removal of a game object
				Notify(Event::GAME_OBJECT_REMOVED, *objectsToRemove[i]);
				gameObjects.erase(std::remove(gameObjects.begin(), gameObjects.end(), gameObjects[j]));
				objectsToRemove.erase(std::remove(objectsToRemove.begin(), objectsToRemove.end(), objectsToRemove[i]), objectsToRemove.end());
				return;
			}
		}
	}
}

void EntityManager::ClearGUIElements()
{
	for (int i = guiElementsToRemove.size() - 1; i >= 0; i--)
	{
		Notify(Event::GUI_ELEMENT_REMOVED, guiElementsToRemove[i]);
		guiElementsToRemove.erase(std::remove(guiElementsToRemove.begin(), guiElementsToRemove.end(), guiElementsToRemove[i]));
	}
}

void EntityManager::AddGameObjects()
{
	while (!objectsToAdd.empty())
	{
		Notify(Event::GAME_OBJECT_ADDED, *objectsToAdd.front());
		gameObjects.emplace_back(std::move(objectsToAdd.front()));
		objectsToAdd.pop();
	}

	for (int i = guiElementsToAdd.size() - 1; i >= 0; i--)
	{
		Notify(Event::GUI_ELEMENT_ADDED, guiElementsToAdd[i]);
		guiElementsToAdd.erase(std::remove(guiElementsToAdd.begin(), guiElementsToAdd.end(), guiElementsToAdd[i]));
	}
}

EntityManager* EntityManager::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new EntityManager();
	}
	return instance;
}

//Using this to inform other subsystems of game object related events
void EntityManager::OnNotify(Event event)
{
	Notify(event);
}

void EntityManager::OnNotify(Event event, GameObject& gameObject)
{
	Notify(event, gameObject);
}
