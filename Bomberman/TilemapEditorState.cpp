#include "TilemapEditorState.h"

#include "MainMenuState.h"
#include "TilemapManager.h"
#include "InputHandler.h"
#include "EntityManager.h"

void TilemapEditorState::PlaceTile(glm::vec2 mousePos)
{
	placedTile = true;
	if (TilemapManager::GetInstance()->IsValidPosition(mousePos))
	{
		TilemapManager::GetInstance()->PlaceTile(mousePos);
	}
}

TilemapEditorState::TilemapEditorState(std::shared_ptr<StateMachine> stateMachine, std::shared_ptr<sf::RenderWindow> window) : State(stateMachine, window)
{
	editorUI = std::make_unique<TilemapEditorUI>();
	placedTile = false;
}

void TilemapEditorState::EnterState()
{	
	editorUI->Open();
	editorUI->AddObserver(this);
	TilemapManager::GetInstance()->OpenEditor();
	Notify(Event::OPEN_EDITOR);
}

void TilemapEditorState::UpdateState(float deltaTime)
{
	if (InputHandler::GetMouseButton(sf::Mouse::Left) && !placedTile)
	{
		auto mousePos = sf::Mouse::getPosition(*window);
		if (!editorUI->MouseOnUI(mousePos))
		{
			PlaceTile(glm::vec2(mousePos.x, mousePos.y));
		}
	}
	if (placedTile && !InputHandler::GetMouseButton(sf::Mouse::Left))
	{
		placedTile = false;
	}
}

void TilemapEditorState::ExitState()
{
	editorUI->Close();
	TilemapManager::GetInstance()->Clear();
	EntityManager::GetInstance()->RemoveAllGameObjects();
}

void TilemapEditorState::OnNotify(Event event)
{
	switch (event)
	{
	case Event::OPEN_MAIN_MENU:
		stateMachine->SwitchState(std::make_unique<MainMenuState>(stateMachine, window));
		break;
	case Event::EXIT_GAME:
		window->close();
		break;
	}
}
