#include "Animation.h"

sf::Sprite* Animation::PlayAnimation(float deltaTime)
{
    if (isFinished)
    {
        return sprite.get();
    }

    timer += deltaTime;
    if (timer >= duration / frames.size())
    {
        if (!shouldLoop && currentFrame == frames.size() - 1)
        {
            isFinished = true;
        }
        sprite->setTextureRect(frames[currentFrame]);
        currentFrame = currentFrame == frames.size() - 1 ? currentFrame = 0 : currentFrame + 1;
        timer = 0;
    }
    return sprite.get();
}

Animation::Animation(std::string pathName, int xSprites, int ySprites, int targetWidth, int targetHeight, float duration, bool shouldLoop)
{
    this->duration = duration;
    this->shouldLoop = shouldLoop;

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

    //This works for sprite sheets that are alligned vertically
    if (ySprites > 1)
    {
        for (int i = 0; i < ySprites; i++)
        {
            frames.emplace_back(sf::IntRect(0, spriteHeight * i, spriteWidth, spriteHeight));
        }
    }

    //This works for sprite sheets that are alligned horizontally
    if (xSprites > 1)
    {
        for (int i = 0; i < xSprites; i++)
        {
            frames.emplace_back(sf::IntRect(spriteWidth * i, 0, spriteWidth, spriteHeight));
        }
    }
}

