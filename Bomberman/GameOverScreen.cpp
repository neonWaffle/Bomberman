#include "GameOverScreen.h"
#include "EntityManager.h"
#include "TilemapManager.h"
#include "TilemapConfig.h"

void GameOverScreen::Open(int winnerId)
{
	tgui::Theme theme{ "Assets/Sprites/UI/theme.txt" };

	gameOverPanel = tgui::Panel::create();
	gameOverPanel->setRenderer(theme.getRenderer("Background"));
	gameOverPanel->setOrigin(0.5f, 0.5f);
	gameOverPanel->setPosition("50%", "50%");
	gameOverPanel->setSize(TilemapConfig::screenWidth, TilemapConfig::screenHeight);

	auto winnerText = tgui::Label::create();
	winnerText->setRenderer(theme.getRenderer("Label"));
	winnerText->setText("Player " + std::to_string(winnerId) + " won!");
	winnerText->setPosition("50%", "20%");
	winnerText->setSize("100%", "20%");
	winnerText->setTextSize(100);
	winnerText->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Center);
	winnerText->setOrigin(0.5f, 0.5f);

	gameOverPanel->add(winnerText);

	auto restartButton = tgui::Button::create("Restart\n");
	restartButton->setRenderer(theme.getRenderer("Button"));
	restartButton->setPosition("50%", "40%");
	restartButton->setSize("10%", "5%");
	restartButton->setTextSize(30);
	restartButton->setOrigin(0.5f, 0.5f);
	restartButton->onPress([this]() { TilemapManager::GetInstance()->Replay(); });

	gameOverPanel->add(restartButton);

	auto mainMenuButton = tgui::Button::create("Main menu\n");
	mainMenuButton->setRenderer(theme.getRenderer("Button"));
	mainMenuButton->setPosition("50%", "46%");
	mainMenuButton->setSize("10%", "5%");
	mainMenuButton->setTextSize(30);
	mainMenuButton->setOrigin(0.5f, 0.5f);
	mainMenuButton->onPress([this]() { Notify(Event::OPEN_MAIN_MENU); });

	gameOverPanel->add(mainMenuButton);

	auto exitButton = tgui::Button::create("Exit\n");
	exitButton->setRenderer(theme.getRenderer("Button"));
	exitButton->setPosition("50%", "52%");
	exitButton->setSize("10%", "5%");
	exitButton->setTextSize(30);
	exitButton->setOrigin(0.5f, 0.5f);
	exitButton->onPress([this]() { Notify(Event::EXIT_GAME); });

	gameOverPanel->add(exitButton);

	EntityManager::GetInstance()->AddGUIElement(gameOverPanel);
}

void GameOverScreen::Close()
{
	EntityManager::GetInstance()->RemoveGUIElement(gameOverPanel);
	EntityManager::GetInstance()->RemoveAllGameObjects();
}