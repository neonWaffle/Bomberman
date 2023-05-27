#pragma once

#include <vector>
#include <ctime>
#include <chrono>

#include <SFML/Graphics.hpp>

class StateMachine;
class Subsystem;

using namespace std::chrono;

class GameEngine
{
private:
	std::shared_ptr<sf::RenderWindow> window;
	std::shared_ptr<StateMachine> stateMachine;
	std::vector<std::unique_ptr<Subsystem>> subsystems;

	float deltaTime;
	high_resolution_clock::time_point currentTime;
	high_resolution_clock::time_point prevTime;
public:
	GameEngine();
	~GameEngine();

	void Init();
	void Run();
	void Close();
};

