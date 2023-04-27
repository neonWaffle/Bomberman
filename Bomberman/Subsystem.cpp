#include "Subsystem.h"
#include "EntityManager.h"

Subsystem::Subsystem()
{
}

Subsystem::~Subsystem()
{
}

void Subsystem::Update(float deltaTime)
{
}

void Subsystem::Init()
{
}

void Subsystem::Close()
{
}

void Subsystem::AddGameObject(GameObject& object)
{
}

void Subsystem::RemoveGameObject(GameObject& object)
{
}

void Subsystem::OnNotify(Event event, GameObject& object)
{
	switch (event)
	{
	case Event::GAME_OBJECT_ADDED:
		AddGameObject(object);
		break;
	case Event::GAME_OBJECT_REMOVED:
		RemoveGameObject(object);
		break;
	}
}

