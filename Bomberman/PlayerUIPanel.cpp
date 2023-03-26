#include "PlayerUIPanel.h"

void PlayerUIPanel::UpdateLives()
{
	if (currentLives >= 1)
	{
		livesIndicators[currentLives - 1]->getRenderer()->setTexture("Assets/Sprites/UI/emptyHealth.png");
		currentLives--;
	}
}

PlayerUIPanel::PlayerUIPanel(float xPos, float yPos, int maxLives, int playerId)
{
	tgui::Theme theme{ "Assets/Sprites/UI/theme.txt" };

	this->playerId = playerId;
	currentLives = maxLives;
	panel = tgui::Panel::create();
	panel->setRenderer(theme.getRenderer("Panel"));
	panel->setOrigin(0.5f, 0.5f);
	panel->setSize(250, 120);
	panel->setPosition(xPos, yPos);
	float indicatorSize = 50;
	tgui::Label::Ptr playerName = tgui::Label::create("Player " + std::to_string(playerId));
	playerName->setPosition(5, 0);
	playerName->setRenderer(theme.getRenderer("TextArea"));
	playerName->setVerticalAlignment(tgui::Label::VerticalAlignment::Top);
	playerName->setTextSize(40);
	playerName->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Left);
	panel->add(playerName);
	for (int i = 0; i < maxLives; i++)
	{
		tgui::Picture::Ptr indicator = tgui::Picture::create();
		indicator->getRenderer()->setTexture("Assets/Sprites/UI/fullHealth.png");
		indicator->setPosition(i * indicatorSize, 50);
		indicator->setSize(indicatorSize, indicatorSize);
		livesIndicators.emplace_back(indicator);
		panel->add(indicator);
	}
}

void PlayerUIPanel::OnNotify(Event event, GameObject& gameObject)
{
	switch (event)
	{
	case Event::PLAYER_DAMAGED:
		auto* player = dynamic_cast<Player*>(&gameObject);
		if (player != nullptr && player->GetPlayerId() == playerId)
		{
			UpdateLives();
		}
		break;
	}
}

tgui::Panel::Ptr PlayerUIPanel::GetPanel()
{
	return panel;
}
