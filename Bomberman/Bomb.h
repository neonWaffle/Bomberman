#pragma once
#include "GameObject.h"
#include "Subject.h"
#include <b2_math.h>

class Bomb : public GameObject, public Subject
{
private:
	float timeTilExplosion;
	float timer;
	int strength;
	bool hasExploded;
	bool SpawnExplosions(b2Vec2 startPoint, b2Vec2 endPoint, glm::vec2 spawnPoint);
public:
	Bomb(glm::vec2 position, int strength);
	virtual ~Bomb();
	void Update(float deltaTime) override;
	void Explode();
	void Detonate();
};

