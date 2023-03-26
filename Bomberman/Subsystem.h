#pragma once
#include "GameObject.h"
#include "EntityManager.h"
#include "Observer.h"
#include <stdio.h>
#include <iostream>
#include "glm/gtx/string_cast.hpp"

class Subsystem : public Observer
{
public:
	Subsystem();
	virtual ~Subsystem() = 0;
	virtual void Update(float deltaTime);
	virtual void Init();
	virtual void Close();
	virtual void AddGameObject(GameObject& object);
	virtual void RemoveGameObject(GameObject& object);
	virtual void OnNotify(Event event, GameObject& object);
};