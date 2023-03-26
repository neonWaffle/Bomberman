#pragma once
#include "State.h"
#include "MainMenuState.h"
#include "Observer.h"
#include "TilemapEditorUI.h"
#include "TilemapManager.h"

class TilemapEditorState : public State
{
private:
	std::unique_ptr<TilemapEditorUI> editorUI;
	bool placedTile;
	void PlaceTile(glm::vec2 mousePos);
public:
	TilemapEditorState(std::shared_ptr<StateMachine> stateMachine, std::shared_ptr<sf::RenderWindow> window);
	void EnterState() override;
	void UpdateState(float deltaTime) override;
	void ExitState() override;
	void OnNotify(Event event) override;
};

