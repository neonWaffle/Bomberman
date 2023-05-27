#include "GraphicsComponent.h"

#include "Animation.h"
#include "ResourceManager.h"

#include "glm.hpp"

GraphicsComponent::GraphicsComponent(const std::string& pathName, int xSprites, int ySprites, int targetWidth, int targetHeight)
{
	auto texture = ResourceManager::GetInstance()->LoadTexture(pathName);
	texture->loadFromFile(pathName);

	int spriteWidth = texture->getSize().x / xSprites;
	int spriteHeight = texture->getSize().y / ySprites;

	sprite = std::make_unique<sf::Sprite>(*texture, sf::IntRect(0, 0, spriteWidth, spriteHeight));
	sprite->setPosition(0.0f, 0.0f);
	sprite->setOrigin(spriteWidth * 0.5f, spriteHeight * 0.5f);

	float xScale = (float)targetWidth / spriteWidth;
	float yScale = (float)targetHeight / spriteHeight;

	sprite->setScale(xScale, yScale);
}

GraphicsComponent::~GraphicsComponent()
{
}

sf::Sprite* GraphicsComponent::GetSprite(glm::vec2 position, float deltaTime)
{
	if (playAnimation)
	{
		sf::Sprite* sprite = animations[currentAnimTitle]->PlayAnimation(deltaTime);
		sprite->setPosition(position.x, position.y);
		if (isFlipped && sprite->getScale().x > 0)
		{
			sprite->setScale(-sprite->getScale().x, sprite->getScale().y);
		}
		else if (!isFlipped && sprite->getScale().x < 0)
		{
			sprite->setScale(-sprite->getScale().x, sprite->getScale().y);
		}
		return sprite;
	}
	else
	{
		sprite->setPosition(position.x, position.y);
		if (isFlipped && sprite->getScale().x > 0)
		{
			sprite->setScale(-sprite->getScale().x, sprite->getScale().y);
		}
		else if (!isFlipped && sprite->getScale().x < 0)
		{
			sprite->setScale(-sprite->getScale().x, sprite->getScale().y);
		}
		return sprite.get();
	}
}

void GraphicsComponent::AddAnimation(const std::string& title, std::unique_ptr<Animation> animation)
{
	animations.emplace(title, std::move(animation));
}

void GraphicsComponent::SwitchAnimation(const std::string& title)
{
	if (currentAnimTitle == title)
		return;

	currentAnimTitle = title;
	playAnimation = true;
}

void GraphicsComponent::Flip(bool flip)
{
	isFlipped = flip;
}
