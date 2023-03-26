#include "GameOverScreen.h"

void GameOverScreen::Open(int winnerId)
{
	tgui::Theme theme{ "Assets/Sprites/UI/theme.txt" };

	gameOverPanel = tgui::Panel::create();
	gameOverPanel->setRenderer(theme.getRenderer("Background"));
	gameOverPanel->setOrigin(0.5f, 0.5f);
	gameOverPanel->setPosition("50%", "50%");
	gameOverPanel->setSize(TilemapConfig::screenWidth, TilemapConfig::screenHeight);

	tgui::Label::Ptr winnerText = tgui::Label::create();
	winnerText->setRenderer(theme.getRenderer("Label"));
	winnerText->setText("Player " + std::to_string(winnerId) + " won!");
	winnerText->setPosition("50%", "20%");
	winnerText->setSize(750, 150);
	winnerText->setTextSize(100);
	winnerText->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Center);
	winnerText->setOrigin(0.5f, 0.5f);

	tgui::Button::Ptr restartButton = tgui::Button::create("Restart\n");
	restartButton->setRenderer(theme.getRenderer("Button"));
	restartButton->setPosition("50%", "50%");
	restartButton->setSize(150, 70);
	restartButton->setTextSize(30);
	restartButton->setOrigin(0.5f, 0.5f);
	restartButton->onPress([this]() { TilemapManager::GetInstance()->Replay(); });

	tgui::Button::Ptr mainMenuButton = tgui::Button::create("Main menu\n");
	mainMenuButton->setRenderer(theme.getRenderer("Button"));
	mainMenuButton->setPosition("50%", "55%");
	mainMenuButton->setSize(150, 70);
	mainMenuButton->setTextSize(30);
	mainMenuButton->setOrigin(0.5f, 0.5f);
	mainMenuButton->onPress([this]() { Notify(Event::OPEN_MAIN_MENU); });

	tgui::Button::Ptr exitButton = tgui::Button::create("Exit\n");
	exitButton->setRenderer(theme.getRenderer("Button"));
	exitButton->setPosition("50%", "60%");
	exitButton->setSize(150, 70);
	exitButton->setTextSize(30);
	exitButton->setOrigin(0.5f, 0.5f);
	exitButton->onPress([this]() { Notify(Event::EXIT_GAME); });

	gameOverPanel->add(winnerText);
	gameOverPanel->add(restartButton);
	gameOverPanel->add(mainMenuButton);
	gameOverPanel->add(exitButton);

	EntityManager::GetInstance()->AddGUIElement(gameOverPanel);
}

void GameOverScreen::Close()
{
	EntityManager::GetInstance()->RemoveGUIElement(gameOverPanel);
	EntityManager::GetInstance()->RemoveAllGameObjects();
}