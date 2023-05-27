#include "PlayerUIPanel.h"

#include "Player.h"

void PlayerUIPanel::UpdateLives()
{
	if (currentLives >= 1)
	{
		lifeIndicators[currentLives - 1]->getRenderer()->setTexture("Assets/Sprites/UI/emptyHealth.png");
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
	panel->setSize("15%", "10%");
	panel->setPosition(xPos, yPos);

	auto playerName = tgui::Label::create("Player " + std::to_string(playerId));
	playerName->setPosition("1%", 0);
	playerName->setRenderer(theme.getRenderer("TextArea"));
	playerName->setVerticalAlignment(tgui::Label::VerticalAlignment::Top);
	playerName->setTextSize(40);
	playerName->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Left);
	panel->add(playerName);

	float height = panel->getSize().y * 0.4f;
	for (int i = 0; i < maxLives; i++)
	{
		auto indicator = tgui::Picture::create();
		indicator->getRenderer()->setTexture("Assets/Sprites/UI/fullHealth.png");
		indicator->setPosition(tgui::Layout("parent.height * 0.4f") * i, "parent.height * 0.4f");
		indicator->setSize("parent.height * 0.4f");
		lifeIndicators.emplace_back(indicator);
		panel->add(indicator);
	}
}

void PlayerUIPanel::OnNotify(Event event, GameObject& gameObject)
{
	switch (event)
	{
	case Event::PLAYER_DAMAGED:
		auto player = dynamic_cast<Player*>(&gameObject);
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
