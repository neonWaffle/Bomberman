#pragma once

#include "GameObject.h"
#include "Observer.h"
#include "Subject.h"

class Player : public GameObject, public Observer, public Subject
{
private:
	float speed;
	glm::vec2 dir;
	int activeBombs;
	int maxBombs;
	int maxLives;
	int livesLeft;
	int bombStrength;
	bool triedPlacingBomb;
	bool isDead;
	int playerId;
	float maxSpeed;
	float immunityDuration;
	float immunityTimer;
	bool isImmune;

	void RemoveActiveBomb();
	void HandleControls();
	void PlaceBomb();
public:
	Player(glm::vec2 position, int playerId);
	virtual ~Player();

	void Update(float deltaTime) override;

	void OnNotify(Event event) override;

	void IncreaseBombAmount();
	void IncreaseBombStrength();
	void IncreaseSpeed(float amount);
	
	void TakeDamage();
	void Die();
	void Kill();
	
	int GetPlayerId();
	int GetMaxLives();
};

