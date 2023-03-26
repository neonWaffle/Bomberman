#pragma once
#include "GameObject.h"
#include "Bomb.h"
#include "Observer.h"

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
public:
	Player(glm::vec2 position, int playerId);
	virtual ~Player();
	void Update(float deltaTime) override;
	void OnNotify(Event event) override;
	void IncreaseBombAmount();
	void IncreaseBombStrength();
	void IncreaseSpeed(float amount);
	void PlaceBomb();
	void GetDamaged();
	void Die();
	void GetKilled();
	int GetPlayerId();
	void HandleControls();
	int GetMaxLives();
};

