#include "PhysicsComponent.h"

#include "RaycastCallback.h"
#include "Converter.h"

#include <glm.hpp>

b2Body* PhysicsComponent::GetBody()
{
	return body;
}

b2Fixture* PhysicsComponent::Raycast(b2Vec2 startPoint, b2Vec2 endPoint)
{
	RaycastCallback raycastCallback;
	body->GetWorld()->RayCast(&raycastCallback, startPoint, endPoint);
	return raycastCallback.GetFixture();
}

PhysicsComponent::PhysicsComponent(bool isDynamic, glm::vec2 size, bool isTrigger, bool isBox, float friction, float density)
{
	this->isDynamic = isDynamic;
	this->isTrigger = isTrigger;
	body = nullptr;
	this->size = size;
	this->friction = friction;
	this->density = density;
	this->isBox = isBox;
}

PhysicsComponent::~PhysicsComponent()
{
}

void PhysicsComponent::SetPhysicsComponent(b2World& world, glm::vec2 position, GameObject& object)
{
	b2BodyDef bodyDef;
	bodyDef.type = isDynamic ? b2_dynamicBody : b2_staticBody;
	bodyDef.position.Set(Converter::GraphicsToPhysics(position.x), Converter::GraphicsToPhysics(position.y));
	bodyDef.fixedRotation = true;
	body = world.CreateBody(&bodyDef);
	body->GetUserData().pointer = (uintptr_t)&object;

	if (isBox)
	{
		b2PolygonShape box;
		box.SetAsBox(Converter::GraphicsToPhysics(size.x), Converter::GraphicsToPhysics(size.y));
		b2FixtureDef fixtureDef;
		fixtureDef.shape = &box;
		fixtureDef.density = density;
		fixtureDef.friction = friction;
		fixtureDef.isSensor = isTrigger;
		body->CreateFixture(&fixtureDef);
	}
	else
	{
		b2CircleShape circle;
		circle.m_p.Set(0, 0);
		circle.m_radius = Converter::GraphicsToPhysics(size.x);
		b2FixtureDef fixtureDef;
		fixtureDef.shape = &circle;
		fixtureDef.density = density;
		fixtureDef.friction = friction;
		fixtureDef.isSensor = isTrigger;
		body->CreateFixture(&fixtureDef);
	}
}

void PhysicsComponent::Move(glm::vec2 velocity)
{
	body->SetLinearVelocity(b2Vec2(velocity.x, velocity.y));
}

glm::vec2 PhysicsComponent::GetPosition()
{
	return glm::vec2(body->GetPosition().x, body->GetPosition().y);
}
