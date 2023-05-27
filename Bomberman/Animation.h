#pragma once

#include <SFML/Graphics.hpp>

class Animation
{
private:
	std::vector<sf::IntRect> frames;
	std::unique_ptr<sf::Sprite> sprite;

	float timer = 0;
	int currentFrame = 0;

	float duration;
	bool shouldLoop;
	bool isFinished;
public:
	Animation(const std::string& pathName, int xSprites, int ySprites, int targetWidth, int targetHeight, float duration, bool shouldLoop = true);

	sf::Sprite* PlayAnimation(float deltaTime);
};

