#pragma once
#include "Component.h"
#include <vector>
#include <box2d/b2_math.h>
#include <box2d/b2_world.h>
#include <box2d/b2_body.h>
#include <box2d/b2_polygon_shape.h>
#include <box2d/b2_fixture.h>
#include <b2_world_callbacks.h>
#include <glm.hpp>

class GameObject;

class PhysicsComponent : public Component
{
private:
	b2Body* body;
	bool isDynamic;
	bool isTrigger;
	bool isBox;
	glm::vec2 size;
	float friction;
	float density;
public:
	PhysicsComponent(bool isDynamic, glm::vec2 size, bool isTrigger = false, bool isBox = true, float friction = 0.3f, float density = 1.0f);
	virtual ~PhysicsComponent();
	void SetPhysicsComponent(b2World& world, glm::vec2 position, GameObject& object);
	void Move(glm::vec2 velocity);
	glm::vec2 GetPosition();
	b2Body* GetBody();
	b2Fixture* Raycast(b2Vec2 startPoint, b2Vec2 endPoint);
};

