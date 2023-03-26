#pragma once
#include "Component.h"
#include "Animation.h"
#include <SFML/Graphics.hpp>
#include <unordered_map>

class GraphicsComponent : public Component
{
private:
	std::unique_ptr<sf::Texture> texture;
	std::unique_ptr<sf::Sprite> sprite;
	std::map<std::string, std::unique_ptr<Animation>> animations;
	bool playAnimation;
	std::string currentAnimTitle;
	bool isFlipped = false;
public:
	GraphicsComponent(std::string pathName, int xSprites, int ySprites, int targetWidth, int targetHeight);
	virtual ~GraphicsComponent();
	sf::Sprite* GetSprite(glm::vec2 position, float deltaTime);
	void AddAnimation(std::string title, std::unique_ptr<Animation> animation);
	void SwitchAnimation(std::string title);
	void Flip(bool flip);
};

