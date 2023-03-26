#include "Player.h"

Player::Player(glm::vec2 position, int playerId) : GameObject("Player")
{
	maxLives = 3;
	livesLeft = maxLives;
	this->speed = 5.0f;
	this->maxBombs = 1;
	this->bombStrength = 2;
	this->playerId = playerId;
	immunityDuration = 1.0f;
	immunityTimer = 0.0f;
	isImmune = false;
	activeBombs = 0;
	isDead = false;
	dir = glm::vec2(0.0f, 0.0f);
	maxSpeed = 12.0f;
	triedPlacingBomb = false;

	int width = 36;
	int height = 72;
	AddComponent(std::move(std::make_unique<TransformComponent>(position, 0.0f)));
	AddComponent(std::move(std::make_unique<PhysicsComponent>(true, glm::vec2(height * 0.45f), false, false)));
	if (playerId == 1)
	{
		AddComponent(std::move(std::make_unique<GraphicsComponent>("Assets/Sprites/Player/playerOneIdle.png", 1, 6, width, height)));
		auto* graphicsComponent = GetComponent<GraphicsComponent>();
		auto animation = std::make_unique<Animation>("Assets/Sprites/Player/playerOneIdle.png", 1, 6, width, height, 1.0f);
		graphicsComponent->AddAnimation("Idle", std::move(animation));
		animation = std::make_unique<Animation>("Assets/Sprites/Player/playerOneRun.png", 1, 8, width, height, 1.3f);
		graphicsComponent->AddAnimation("Walk", std::move(animation));
		graphicsComponent->SwitchAnimation("Idle");
	}
	else if (playerId == 2)
	{
		AddComponent(std::move(std::make_unique<GraphicsComponent>("Assets/Sprites/Player/playerTwoIdle.png", 1, 6, width, height)));
		auto* graphicsComponent = GetComponent<GraphicsComponent>();
		auto animation = std::make_unique<Animation>("Assets/Sprites/Player/playerTwoIdle.png", 1, 6, width, height, 1.0f);
		graphicsComponent->AddAnimation("Idle", std::move(animation));
		animation = std::make_unique<Animation>("Assets/Sprites/Player/playerTwoRun.png", 1, 8, width, height, 1.3f);
		graphicsComponent->AddAnimation("Walk", std::move(animation));
		graphicsComponent->SwitchAnimation("Idle");
	}
}

Player::~Player()
{
}

void Player::Update(float deltaTime)
{
	if (isImmune)
	{
		immunityTimer += deltaTime;
		if (immunityTimer >= immunityDuration)
		{
			isImmune = false;
			immunityTimer = 0.0f;
		}
	}
	HandleControls();
	GetComponent<PhysicsComponent>()->Move(dir * speed * deltaTime);
	if (dir != glm::vec2(0, 0))
		GetComponent<GraphicsComponent>()->SwitchAnimation("Walk");
	else
		GetComponent<GraphicsComponent>()->SwitchAnimation("Idle");
	dir.y = 0;
	dir.x = 0;
}

void Player::OnNotify(Event event)
{
	switch (event)
	{
		case Event::BOMB_EXPLODED:
			RemoveActiveBomb();
			break;
		case Event::BOMB_DETONATED:
			RemoveActiveBomb();
			break;
	}
}

void Player::RemoveActiveBomb()
{
	activeBombs--;
}

void Player::IncreaseBombAmount()
{
	maxBombs++;
}

void Player::IncreaseBombStrength()
{
	bombStrength++;
}

void Player::IncreaseSpeed(float amount)
{
	if (speed < maxSpeed)
	{
		speed += amount;
		speed = std::min(speed, maxSpeed);
	}
}

void Player::PlaceBomb()
{
	if (activeBombs < maxBombs)
	{
		activeBombs++;
		auto bomb = std::make_unique<Bomb>(GetComponent<TransformComponent>()->GetPosition(), bombStrength);
		bomb->AddObserver(this);
		EntityManager::GetInstance()->AddGameObject(std::move(bomb));
	}
}

void Player::GetDamaged()
{
	if (!isImmune && !isDead)
	{
		isImmune = true;
		livesLeft--;
		Notify(Event::PLAYER_DAMAGED, *this);
		if (livesLeft <= 0 && !isDead)
			Die();
	}
}

void Player::Die()
{
	isDead = true;
	Notify(Event::PLAYER_DIED, *this);
}

void Player::GetKilled()
{
	if (!isDead)
		Die();
}

int Player::GetPlayerId()
{
	return playerId;
}

void Player::HandleControls()
{
	if (playerId == 1)
	{
		if (InputHandler::GetKey(sf::Keyboard::W))
			dir.y = -1;
		if (InputHandler::GetKey(sf::Keyboard::S))
			dir.y = 1;
		if (InputHandler::GetKey(sf::Keyboard::A))
		{
			GetComponent<GraphicsComponent>()->Flip(true);
			dir.x = -1;
		}
		if (InputHandler::GetKey(sf::Keyboard::D))
		{
			GetComponent<GraphicsComponent>()->Flip(false);
			dir.x = 1;
		}
		if (InputHandler::GetKey(sf::Keyboard::Space) && !triedPlacingBomb)
		{
			triedPlacingBomb = true;
			PlaceBomb();
		}
		if (triedPlacingBomb && !InputHandler::GetKey(sf::Keyboard::Space))
			triedPlacingBomb = false;
	}
	else if (playerId == 2)
	{
		if (InputHandler::GetKey(sf::Keyboard::Up))
			dir.y = -1;
		if (InputHandler::GetKey(sf::Keyboard::Down))
			dir.y = 1;
		if (InputHandler::GetKey(sf::Keyboard::Left))
		{
			GetComponent<GraphicsComponent>()->Flip(true);
			dir.x = -1;
		}
		if (InputHandler::GetKey(sf::Keyboard::Right))
		{
			GetComponent<GraphicsComponent>()->Flip(false);
			dir.x = 1;
		}
		if (InputHandler::GetKey(sf::Keyboard::Slash) && !triedPlacingBomb)
		{
			triedPlacingBomb = true;
			PlaceBomb();
		}
		if (triedPlacingBomb && !InputHandler::GetKey(sf::Keyboard::Slash))
			triedPlacingBomb = false;
	}
}

int Player::GetMaxLives()
{
	return maxLives;
}
