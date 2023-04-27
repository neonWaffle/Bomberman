#include "Bomb.h"
#include "Explosion.h"
#include "TilemapConfig.h"
#include "TransformComponent.h"
#include "PhysicsComponent.h"
#include "GraphicsComponent.h"
#include "Animation.h"
#include "EntityManager.h"
#include "Converter.h"

Bomb::Bomb(glm::vec2 position, int strength) : GameObject("Bomb")
{
	//Makes the bomb snap to the tile
	position = glm::vec2((int)((position.x - TilemapConfig::xTilemapOffset) / TilemapConfig::tileSize) * TilemapConfig::tileSize + TilemapConfig::tileSize * 0.5f + TilemapConfig::xTilemapOffset,
		(int)((position.y - TilemapConfig::yTilemapOffset) / TilemapConfig::tileSize) * TilemapConfig::tileSize + TilemapConfig::tileSize * 0.5f + TilemapConfig::yTilemapOffset);

	AddComponent(std::make_unique<TransformComponent>(position, 0.0f));
	AddComponent(std::make_unique<PhysicsComponent>(true, glm::vec2(TilemapConfig::tileSize * 0.5f, TilemapConfig::tileSize * 0.5f), true));
	AddComponent(std::make_unique<GraphicsComponent>("Assets/Sprites/Objects/bomb.png", 1, 1, TilemapConfig::tileSize, TilemapConfig::tileSize));

	auto* graphicsComponent = GetComponent<GraphicsComponent>();
	auto animation = std::make_unique<Animation>("Assets/Sprites/Objects/bomb.png", 3, 1, TilemapConfig::tileSize, TilemapConfig::tileSize, 0.8f);
	graphicsComponent->AddAnimation("Idle", std::move(animation));
	graphicsComponent->SwitchAnimation("Idle");

	timeTilExplosion = 3.0f;
	timer = 0.0f;
	this->strength = strength;
	hasExploded = false;
}

Bomb::~Bomb()
{
}

void Bomb::Update(float deltaTime)
{
	timer += deltaTime;
	if (timer >= timeTilExplosion && !hasExploded)
	{
		Explode();
	}
}

//Checks if there are any tiles that would block the explosions before spawning them
bool Bomb::SpawnExplosions(b2Vec2 startPoint, b2Vec2 endPoint, glm::vec2 spawnPoint)
{
	auto* physicsComponent = GetComponent<PhysicsComponent>();
	b2Fixture* fixture = physicsComponent->Raycast(startPoint, endPoint);

	if (fixture != nullptr)
	{
		b2BodyUserData& bodyData = fixture->GetBody()->GetUserData();
		GameObject* object = reinterpret_cast<GameObject*>(bodyData.pointer);
		std::string tag = object->GetTag();

		if (tag == "WallTile" || tag == "EndTile")
		{
			return false;
		}
		else if (tag == "BoxTile")
		{
			auto explosion = std::make_unique<Explosion>(spawnPoint);
			EntityManager::GetInstance()->AddGameObject(std::move(explosion));
			return false;
		}
		else
		{
			auto explosion = std::make_unique<Explosion>(spawnPoint);
			EntityManager::GetInstance()->AddGameObject(std::move(explosion));
			return true;
		}
	}
	else
	{
		auto explosion = std::make_unique<Explosion>(spawnPoint);
		EntityManager::GetInstance()->AddGameObject(std::move(explosion));
		return true;
	}
}

void Bomb::Explode()
{
	if (hasExploded)
		return;

	hasExploded = true;
	auto* physicsComponent = GetComponent<PhysicsComponent>();
	auto* transformComponent = GetComponent<TransformComponent>();
	glm::vec2 spawnPos = transformComponent->GetPosition();
	auto explosion = std::make_unique<Explosion>(spawnPos);
	EntityManager::GetInstance()->AddGameObject(std::move(explosion));

	for (int i = 1; i <= strength; i++)
	{
		b2Vec2 startPoint = b2Vec2(Converter::GraphicsToPhysics(transformComponent->GetPosition().x - (i - 1) * TilemapConfig::tileSize), 
			Converter::GraphicsToPhysics(transformComponent->GetPosition().y));
		b2Vec2 endPoint = b2Vec2(Converter::GraphicsToPhysics(transformComponent->GetPosition().x - i * TilemapConfig::tileSize),
			Converter::GraphicsToPhysics(transformComponent->GetPosition().y));
		if (!SpawnExplosions(startPoint, endPoint, glm::vec2(Converter::PhysicsToGraphics(endPoint.x), Converter::PhysicsToGraphics(endPoint.y))))
			break;
	}

	for (int i = 1; i <= strength; i++)
	{
		b2Vec2 startPoint = b2Vec2(Converter::GraphicsToPhysics(transformComponent->GetPosition().x + (i - 1) * TilemapConfig::tileSize),
			Converter::GraphicsToPhysics(transformComponent->GetPosition().y));
		b2Vec2 endPoint = b2Vec2(Converter::GraphicsToPhysics(transformComponent->GetPosition().x + i * TilemapConfig::tileSize),
			Converter::GraphicsToPhysics(transformComponent->GetPosition().y));
		if (!SpawnExplosions(startPoint, endPoint, glm::vec2(Converter::PhysicsToGraphics(endPoint.x), Converter::PhysicsToGraphics(endPoint.y))))
			break;
	}

	for (int i = 1; i <= strength; i++)
	{
		b2Vec2 startPoint = b2Vec2(Converter::GraphicsToPhysics(transformComponent->GetPosition().x),
			Converter::GraphicsToPhysics(transformComponent->GetPosition().y - (i - 1) * TilemapConfig::tileSize));
		b2Vec2 endPoint = b2Vec2(Converter::GraphicsToPhysics(transformComponent->GetPosition().x),
			Converter::GraphicsToPhysics(transformComponent->GetPosition().y - i * TilemapConfig::tileSize));
		if (!SpawnExplosions(startPoint, endPoint, glm::vec2(Converter::PhysicsToGraphics(endPoint.x), Converter::PhysicsToGraphics(endPoint.y))))
			break;
	}

	for (int i = 1; i <= strength; i++)
	{
		b2Vec2 startPoint = b2Vec2(Converter::GraphicsToPhysics(transformComponent->GetPosition().x),
			Converter::GraphicsToPhysics(transformComponent->GetPosition().y + (i - 1) * TilemapConfig::tileSize));
		b2Vec2 endPoint = b2Vec2(Converter::GraphicsToPhysics(transformComponent->GetPosition().x),
			Converter::GraphicsToPhysics(transformComponent->GetPosition().y + i * TilemapConfig::tileSize));
		if (!SpawnExplosions(startPoint, endPoint, glm::vec2(Converter::PhysicsToGraphics(endPoint.x), Converter::PhysicsToGraphics(endPoint.y))))
			break;
	}

	Notify(Event::BOMB_EXPLODED);
	EntityManager::GetInstance()->RemoveGameObject(this);
}

//Prevents the bomb from exploding if EndTile gets placed on it
void Bomb::Detonate()
{
	hasExploded = true;
	Notify(Event::BOMB_DETONATED);
	EntityManager::GetInstance()->RemoveGameObject(this);
}
