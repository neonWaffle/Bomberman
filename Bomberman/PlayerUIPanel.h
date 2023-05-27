#pragma once

#include "Observer.h"

#include "TGUI/TGUI.hpp"

class GameObject;

class PlayerUIPanel : public Observer
{
private:
	tgui::Panel::Ptr panel;
	std::vector<tgui::Picture::Ptr> lifeIndicators;
	int currentLives;
	int playerId;

	void UpdateLives();
public:
	PlayerUIPanel(float xPos, float yPos, int maxHealth, int playerId);

	void OnNotify(Event event, GameObject& gameObject) override;
	tgui::Panel::Ptr GetPanel();
};

