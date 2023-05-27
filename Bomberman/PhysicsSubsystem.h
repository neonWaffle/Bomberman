#pragma once

#include "Subsystem.h"

#include <b2_world.h>

class ContactListener;

class PhysicsSubsystem : public Subsystem
{
private:
	std::unique_ptr<b2World> world;
	float timeStep;
	int32 velocityIterations;
	int32 positionIterations;
	std::unique_ptr<ContactListener> contactListener;
public:
	PhysicsSubsystem();

	void Init() override;
	void Update(float deltaTime) override;
	void AddGameObject(GameObject& object) override;
	void RemoveGameObject(GameObject& object) override;
};

