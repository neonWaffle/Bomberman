#pragma once
#include "Subsystem.h"
#include "ContactListener.h"
#include "RaycastCallback.h"
#include <box2d/b2_math.h>
#include <box2d/b2_world.h>
#include <box2d/b2_body.h>
#include <box2d/b2_polygon_shape.h>
#include <box2d/b2_fixture.h>
#include <box2d/b2_draw.h>

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

