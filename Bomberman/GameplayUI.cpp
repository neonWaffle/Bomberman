#include "GameplayUI.h"

#include "EntityManager.h"
#include "TilemapConfig.h"

GameplayUI::GameplayUI(std::vector<Player*> players)
{
	float xOffset = TilemapConfig::screenWidth * 0.1f;
	float yOffset = TilemapConfig::screenHeight * 0.1f;

	for (int i = 0; i < players.size(); i++)
	{
		if (i != 0 && i % 2 == 0)
		{
			yOffset += yOffset;
		}
		if (i % 2 != 0)
		{
			playerPanels.emplace_back(std::make_unique<PlayerUIPanel>(TilemapConfig::screenWidth - xOffset, yOffset, players[i]->GetMaxLives(), i + 1));
		}
		else
		{
			playerPanels.emplace_back(std::make_unique<PlayerUIPanel>(xOffset, yOffset, players[i]->GetMaxLives(), i + 1));
		}
		players[i]->AddObserver(playerPanels[i].get());
	}

	tgui::Theme theme{ "Assets/Sprites/UI/theme.txt" };

	timer = tgui::Label::create();
	timer->setRenderer(theme.getRenderer("Timer"));
	timer->setSize("20%", "10%");
	timer->setTextSize(65);
	timer->setPosition("50%", "5%");
	timer->setOrigin(0.5f, 0.5f);
	timer->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Center);
	timer->setVerticalAlignment(tgui::Label::VerticalAlignment::Top);
}

void GameplayUI::Open()
{
	for (int i = 0; i < playerPanels.size(); i++)
	{
		EntityManager::GetInstance()->AddGUIElement(playerPanels[i]->GetPanel());
	}
	EntityManager::GetInstance()->AddGUIElement(timer);
}

void GameplayUI::Close()
{
	for (int i = 0; i < playerPanels.size(); i++)
	{
		EntityManager::GetInstance()->RemoveGUIElement(playerPanels[i]->GetPanel());
	}
	EntityManager::GetInstance()->RemoveGUIElement(timer);
}

void GameplayUI::UpdateTimer(float remainingTime)
{
	std::string min = std::to_string((int)(remainingTime / 60));
	std::string sec = std::to_string((int)(remainingTime) % 60);
	timer->setText(min + ":" + std::string(2 - sec.length(), '0') + sec);
}
