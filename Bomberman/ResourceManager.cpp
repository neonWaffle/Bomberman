#include "ResourceManager.h"

ResourceManager* ResourceManager::instance;

ResourceManager* ResourceManager::GetInstance()
{
    if (instance == nullptr)
    {
        instance = new ResourceManager();
    }
    return instance;
}

sf::Texture* ResourceManager::LoadTexture(const std::string& filePath)
{
    //If the specified texture already exists, no need to load it
    if (textures.count(filePath) > 0)
    {
        return textures[filePath].get();
    }

    auto texture = std::make_unique<sf::Texture>();
    texture->loadFromFile(filePath);
    textures.insert(std::make_pair(filePath, std::move(texture)));
    return textures[filePath].get();
}

sf::Texture* ResourceManager::GetTexture(const std::string& filePath)
{
    return textures.count(filePath) > 0 ? textures[filePath].get() : nullptr;
}
