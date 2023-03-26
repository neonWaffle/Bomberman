#pragma once
#include "Player.h"
#include "StateMachine.h"
#include "AudioSubsystem.h"
#include "GraphicsSubsystem.h"
#include "PhysicsSubsystem.h"
#include "InputHandler.h"
#include "EntityManager.h"
#include "TilemapManager.h"
#include "MainMenu.h"
#include "MainMenuState.h"
#include "GameplayState.h"
#include <vector>
#include <ctime>
#include <chrono>

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

