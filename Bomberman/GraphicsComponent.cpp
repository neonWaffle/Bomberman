#include "GraphicsComponent.h"
#include "glm.hpp"

GraphicsComponent::GraphicsComponent(std::string pathName, int xSprites, int ySprites, int targetWidth, int targetHeight)
{
	texture = std::make_unique<sf::Texture>();
	texture->loadFromFile(pathName);
	int spriteWidth = texture->getSize().x / xSprites;
	int spriteHeight = texture->getSize().y / ySprites;
	sprite = std::make_unique<sf::Sprite>(*texture, sf::IntRect(0, 0, spriteWidth, spriteHeight));
	sprite->setPosition(0.0f, 0.0f);
	float xScale = (float)targetWidth / spriteWidth;
	float yScale = (float)targetHeight / spriteHeight;
	sprite->setScale(xScale, yScale);
	sprite->setOrigin(spriteWidth / 2.0f, spriteHeight / 2.0f);
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

void GraphicsComponent::AddAnimation(std::string title, std::unique_ptr<Animation> animation)
{
	animations.emplace(title, std::move(animation));
}

void GraphicsComponent::SwitchAnimation(std::string title)
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
