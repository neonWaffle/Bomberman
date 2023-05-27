#pragma once

#include <unordered_map>
#include <memory>

#include <SFML/graphics.hpp>

class ResourceManager
{
public:
	ResourceManager(ResourceManager&) = delete;
	void operator=(const ResourceManager&) = delete;
	static ResourceManager* GetInstance();

	sf::Texture* LoadTexture(const std::string& filePath);
	sf::Texture* GetTexture(const std::string& filePath);
private:
	static ResourceManager* instance;
	std::unordered_map<std::string, std::unique_ptr<sf::Texture>> textures;

	ResourceManager() = default;
};

