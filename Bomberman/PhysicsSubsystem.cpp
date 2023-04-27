#include "PhysicsSubsystem.h"
#include "Converter.h"
#include "PhysicsComponent.h"
#include "TransformComponent.h"
#include "EntityManager.h"
#include <box2d/b2_math.h>
#include <box2d/b2_world.h>
#include <box2d/b2_body.h>
#include <box2d/b2_polygon_shape.h>
#include <box2d/b2_fixture.h>
#include <box2d/b2_draw.h>

PhysicsSubsystem::PhysicsSubsystem()
{
}

void PhysicsSubsystem::Init()
{
	b2Vec2 gravity(0.0f, 0.0f);
	world = std::make_unique<b2World>(gravity);

	timeStep = 1.0f / 60.0f;
	velocityIterations = 8;
	positionIterations = 5;

	contactListener = std::make_unique<ContactListener>();

	world->SetContactListener(contactListener.get());
	world->SetAllowSleeping(false);
}

void PhysicsSubsystem::Update(float deltaTime)
{
	for (int32 i = 0; i < 60; i++)
	{
		world->Step(timeStep, velocityIterations, positionIterations);
		for (auto&& object : EntityManager::GetInstance()->gameObjects)
		{
			auto* physicsComponent = object->GetComponent<PhysicsComponent>();
			auto* transformComponent = object->GetComponent<TransformComponent>();
			if (physicsComponent != nullptr && transformComponent != nullptr)
			{
				auto pos = physicsComponent->GetPosition();
				transformComponent->SetPosition(glm::vec2(Converter::PhysicsToGraphics(pos.x), Converter::PhysicsToGraphics(pos.y)));
			}
		}
	}
}

void PhysicsSubsystem::AddGameObject(GameObject& object)
{
	auto* physicsComponent = object.GetComponent<PhysicsComponent>();
	auto* transformComponent = object.GetComponent<TransformComponent>();
	if (physicsComponent != nullptr && transformComponent != nullptr)
	{
		physicsComponent->SetPhysicsComponent(*world, transformComponent->GetPosition(), object);
	}
}

void PhysicsSubsystem::RemoveGameObject(GameObject& object)
{
	auto* physicsComponent = object.GetComponent<PhysicsComponent>();
	if (physicsComponent != nullptr)
	{
		auto* body = physicsComponent->GetBody();
		body->GetWorld()->DestroyBody(body);
	}
}
