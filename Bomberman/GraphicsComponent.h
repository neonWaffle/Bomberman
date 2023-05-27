#pragma once

#include "Animation.h"
#include "Component.h"

#include <unordered_map>
#include <glm.hpp>

#include <SFML/Graphics.hpp>

class GraphicsComponent : public Component
{
private:
	std::unique_ptr<sf::Sprite> sprite;
	std::unordered_map<std::string, std::unique_ptr<Animation>> animations;

	bool playAnimation;
	std::string currentAnimTitle;
	bool isFlipped = false;
public:
	GraphicsComponent(const std::string& pathName, int xSprites, int ySprites, int targetWidth, int targetHeight);
	~GraphicsComponent();

	sf::Sprite* GetSprite(glm::vec2 position, float deltaTime);
	void AddAnimation(const std::string& title, std::unique_ptr<Animation> animation);
	void SwitchAnimation(const std::string& title);
	void Flip(bool flip);
};

