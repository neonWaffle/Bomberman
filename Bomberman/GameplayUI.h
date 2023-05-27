#pragma once
#include "TGUI/TGUI.hpp"
#include "PlayerUIPanel.h"

class GameplayUI
{
private:
	std::vector<std::unique_ptr<PlayerUIPanel>> playerPanels;
	tgui::Label::Ptr timer;
public:
	GameplayUI(std::vector<Player*> players);

	void Open();
	void Close();
	void UpdateTimer(float remainingTime);
};

