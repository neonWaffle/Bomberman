#include "MainMenuState.h"

#include "TilemapEditorState.h"
#include "GameplayState.h"
#include "TilemapManager.h"
#include "MainMenu.h"

MainMenuState::MainMenuState(std::shared_ptr<StateMachine> stateMachine, std::shared_ptr<sf::RenderWindow> window) : State(stateMachine, window)
{
	mainMenu = std::make_unique<MainMenu>();
}

void MainMenuState::EnterState()
{
	mainMenu->Open();
	mainMenu->AddObserver(this);
	TilemapManager::GetInstance()->AddObserver(this);
	Notify(Event::OPEN_MAIN_MENU);
}

void MainMenuState::ExitState()
{
	mainMenu->Close();
	mainMenu->RemoveObserver(this);
	TilemapManager::GetInstance()->RemoveObserver(this);
}

void MainMenuState::OnNotify(Event event)
{
	switch (event)
	{
	case Event::START_GAME:
		stateMachine->SwitchState(std::make_unique<GameplayState>(stateMachine, window));
		break;
	case Event::OPEN_EDITOR:
		stateMachine->SwitchState(std::make_unique<TilemapEditorState>(stateMachine, window));
		break;
	case Event::EXIT_GAME:
		Notify(Event::EXIT_GAME);
		break;
	}
}
