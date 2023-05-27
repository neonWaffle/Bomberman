#pragma once

#include "TGUI/TGUI.hpp"

class PlayerUIPanel;
class Player;

class GameplayUI
{
private:
	std::vector<std::unique_ptr<PlayerUIPanel>> playerPanels;
	tgui::Label::Ptr timer;
public:
	GameplayUI(std::vector<Player*> players);
	~GameplayUI();

	void Open();
	void Close();
	void UpdateTimer(float remainingTime);
};

