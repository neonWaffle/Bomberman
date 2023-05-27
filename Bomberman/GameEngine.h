#pragma once

#include <vector>
#include <ctime>
#include <chrono>

#include <SFML/Graphics.hpp>

class StateMachine;
class Subsystem;

class GameEngine
{
private:
	std::shared_ptr<sf::RenderWindow> window;
	std::shared_ptr<StateMachine> stateMachine;
	std::vector<std::unique_ptr<Subsystem>> subsystems;

	float deltaTime;
	std::chrono::high_resolution_clock::time_point currentTime;
	std::chrono::high_resolution_clock::time_point prevTime;
public:
	GameEngine();
	~GameEngine();

	void Init();
	void Run();
	void Close();
};

