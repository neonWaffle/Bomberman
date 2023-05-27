#include "GameEngine.h"

#include "StateMachine.h"
#include "AudioSubsystem.h"
#include "GraphicsSubsystem.h"
#include "PhysicsSubsystem.h"
#include "InputHandler.h"
#include "EntityManager.h"
#include "TilemapManager.h"
#include "MainMenuState.h"
#include "TilemapConfig.h"

GameEngine::GameEngine()
{
	currentTime = std::chrono::high_resolution_clock::now();
	prevTime = currentTime;
	window = std::make_shared<sf::RenderWindow>(sf::VideoMode(TilemapConfig::screenWidth, TilemapConfig::screenHeight), "Bomberman");
	stateMachine = std::make_shared<StateMachine>();

	subsystems.emplace_back(std::move(std::make_unique<GraphicsSubsystem>(window)));
	subsystems.emplace_back(std::make_unique<PhysicsSubsystem>());

	auto audioSubsystem = std::make_unique<AudioSubsystem>();
	audioSubsystem->AddSound("matchSong", "Assets/Audio/matchSong.mp3");
	audioSubsystem->AddSound("mainMenuSong", "Assets/Audio/mainMenuSong.mp3");
	audioSubsystem->AddSound("gameOverSong", "Assets/Audio/gameOverSong.mp3");
	audioSubsystem->AddSound("tilemapEditorSong", "Assets/Audio/tilemapEditorSong.mp3");
	audioSubsystem->AddSound("explosionSFX", "Assets/Audio/explosionSFX.wav");
	subsystems.emplace_back(std::move(audioSubsystem));
}

GameEngine::~GameEngine()
{
}

void GameEngine::Init()
{
	for (const auto& sub : subsystems)
	{
		sub->Init();
		Observer* observer = dynamic_cast<Observer*>(sub.get());
		if (observer != nullptr)
		{
			EntityManager::GetInstance()->AddObserver(observer);
			stateMachine->AddObserver(observer);
			TilemapManager::GetInstance()->AddObserver(observer);
		}
	}
	stateMachine->SwitchState(std::make_unique<MainMenuState>(stateMachine, window));
}

void GameEngine::Run()
{
	while (stateMachine->GetIsRunning())
	{
		prevTime = currentTime;
		currentTime = std::chrono::high_resolution_clock::now();
		deltaTime = std::chrono::duration<float>(currentTime - prevTime).count();

		stateMachine->Update(deltaTime);

		for (const auto& subsystem : subsystems)
		{
			subsystem->Update(deltaTime);
		}

		EntityManager::GetInstance()->ClearGameObjects();
		EntityManager::GetInstance()->ClearGUIElements();
		EntityManager::GetInstance()->AddGameObjects();
	}
}

void GameEngine::Close()
{
	for (const auto& subsystem : subsystems)
	{
		subsystem->Close();
	}
}
