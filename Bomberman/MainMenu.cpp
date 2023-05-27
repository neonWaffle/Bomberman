#include "MainMenu.h"

#include "EntityManager.h"
#include "TilemapManager.h"
#include "TilemapConfig.h"

#include <filesystem>

void MainMenu::OpenCustomLevelPanel()
{
	tgui::Theme theme{ "Assets/Sprites/UI/theme.txt" };
	mainMenuPanel->setVisible(false);
	customLevelSelectionPanel->setVisible(true);
}

void MainMenu::LoadCustomLevel(const tgui::String& buttonText)
{
	if (!TilemapManager::GetInstance()->PlayInCustomTilemap(buttonText.toStdString()))
	{
		invalidTilemapMessage->setVisible(true);
	}
}

void MainMenu::OpenMainMenuPanel()
{
	invalidTilemapMessage->setVisible(false);
	customLevelSelectionPanel->setVisible(false);
	mainMenuPanel->setVisible(true);
}

MainMenu::MainMenu()
{
	tgui::Theme theme{ "Assets/Sprites/UI/theme.txt" };

	//Main menu UI:
	mainMenuPanel = tgui::Panel::create();
	mainMenuPanel->setRenderer(theme.getRenderer("Background"));
	mainMenuPanel->setPosition(0.0f, 0.0f);
	mainMenuPanel->setSize(TilemapConfig::screenWidth, TilemapConfig::screenHeight);

	auto titleText = tgui::Label::create();
	titleText->setRenderer(theme.getRenderer("Label"));
	titleText->setText("Bomberman");
	titleText->setOrigin(0.5f, 0.5f);
	titleText->setPosition("50%", "30%");
	titleText->setSize("50%", "20%");
	titleText->setTextSize(100);
	titleText->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Center);

	mainMenuPanel->add(titleText);

	auto startButton = tgui::Button::create("Start\n");
	startButton->setRenderer(theme.getRenderer("Button"));
	startButton->setPosition("50%", "40%");
	startButton->setSize("10%", "5%");;
	startButton->setTextSize(30);
	startButton->setOrigin(0.5f, 0.5f);
	startButton->onPress([this]() { TilemapManager::GetInstance()->PlayInDefaultTilemap(); });

	mainMenuPanel->add(startButton);

	auto customLevelButton = tgui::Button::create("Load custom\n");
	customLevelButton->setRenderer(theme.getRenderer("Button"));
	customLevelButton->setPosition("50%", "46%");
	customLevelButton->setSize("10%", "5%");
	customLevelButton->setTextSize(30);
	customLevelButton->setOrigin(0.5f, 0.5f);
	customLevelButton->onPress([this]() { OpenCustomLevelPanel(); });

	mainMenuPanel->add(customLevelButton);

	auto editorButton = tgui::Button::create("Map editor\n");
	editorButton->setRenderer(theme.getRenderer("Button"));
	editorButton->setPosition("50%", "52%");
	editorButton->setSize("10%", "5%");
	editorButton->setTextSize(30);
	editorButton->setOrigin(0.5f, 0.5f);
	editorButton->onPress([this]() { TilemapManager::GetInstance()->OpenEditor(); });

	mainMenuPanel->add(editorButton);

	auto exitButton = tgui::Button::create("Exit\n");
	exitButton->setRenderer(theme.getRenderer("Button"));
	exitButton->setPosition("50%", "58%");
	exitButton->setSize("10%", "5%");
	exitButton->setTextSize(30);
	exitButton->setOrigin(0.5f, 0.5f);
	exitButton->onPress([this]() { Notify(Event::EXIT_GAME); });

	mainMenuPanel->add(exitButton);

	//Custom level selection UI:
	customLevelSelectionPanel = tgui::Panel::create();
	customLevelSelectionPanel->setRenderer(theme.getRenderer("Background"));
	customLevelSelectionPanel->setOrigin(0.5f, 0.5f);
	customLevelSelectionPanel->setPosition("50%", "50%");
	customLevelSelectionPanel->setSize(TilemapConfig::screenWidth, TilemapConfig::screenHeight);

	filePanel = tgui::ScrollablePanel::create();
	filePanel->setRenderer(theme.getRenderer("ScrollablePanel"));
	filePanel->setOrigin(0.5f, 0.5f);
	filePanel->setPosition("50%", "50%");
	filePanel->setSize("30%", "40%");
	filePanel->setVerticalScrollbarPolicy(tgui::Scrollbar::Policy::Always);
	filePanel->setHorizontalScrollbarPolicy(tgui::Scrollbar::Policy::Never);

	customLevelSelectionPanel->add(filePanel);

	auto customLevelSelectionTitle = tgui::Label::create("Custom levels");
	customLevelSelectionTitle->setRenderer(theme.getRenderer("Label"));
	customLevelSelectionTitle->setPosition("50%", "25%");
	customLevelSelectionTitle->setSize("40%", "10%");
	customLevelSelectionTitle->setTextSize(70);
	customLevelSelectionTitle->setOrigin(0.5f, 0.5f);
	customLevelSelectionTitle->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Center);

	customLevelSelectionPanel->add(customLevelSelectionTitle);

	std::string path = "Assets/Levels/Custom";

	int fileId = 0;
	for (const auto& file : std::filesystem::directory_iterator(path))
	{
		if (file.path().extension() == ".map")
		{
			std::string fileName = file.path().string();
			fileName = fileName.substr(path.find_last_of("/") + 1);
			fileName = fileName.substr(fileName.find_last_of("\\") + 1);
			fileName = fileName.substr(0, fileName.size() - 4);

			tgui::Button::Ptr fileButton = tgui::Button::create();
			fileButton->setRenderer(theme.getRenderer("FileButton"));
			fileButton->setPosition(0.0f, tgui::Layout("10%") * fileId);
			fileButton->setSize("100%", "10%");
			fileButton->setText(fileName);
			fileButton->setTextSize(25);
			filePanel->add(fileButton);

			fileButton->onPress([&](const tgui::String& buttonText) { LoadCustomLevel(buttonText); });

			fileId++;
		}
	}

	auto returnButton = tgui::Button::create();
	returnButton->setRenderer(theme.getRenderer("ReturnButton"));
	returnButton->setPosition("10%", "10%");
	returnButton->setSize("parent.height * 0.05f", "parent.height * 0.05f");
	returnButton->setTextSize(30);
	returnButton->setOrigin(0.5f, 0.5f);
	returnButton->onPress([this]() { OpenMainMenuPanel(); });

	customLevelSelectionPanel->add(returnButton);

	invalidTilemapMessage = tgui::Label::create();
	invalidTilemapMessage->setRenderer(theme.getRenderer("ErrorMessage"));
	invalidTilemapMessage->setText("Invalid tilemap!");
	invalidTilemapMessage->setTextSize(20);
	invalidTilemapMessage->setPosition("50%", "72%");
	invalidTilemapMessage->setSize("20%", "5%");
	invalidTilemapMessage->setOrigin(0.5f, 0.5f);
	invalidTilemapMessage->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Center);
	invalidTilemapMessage->setVisible(false);

	customLevelSelectionPanel->add(invalidTilemapMessage);
}

MainMenu::~MainMenu()
{
}

void MainMenu::Open()
{
	EntityManager::GetInstance()->AddGUIElement(mainMenuPanel);
	EntityManager::GetInstance()->AddGUIElement(customLevelSelectionPanel);
	OpenMainMenuPanel();
}

void MainMenu::Close()
{
	EntityManager::GetInstance()->RemoveGUIElement(mainMenuPanel);
	EntityManager::GetInstance()->RemoveGUIElement(customLevelSelectionPanel);
	EntityManager::GetInstance()->RemoveAllGameObjects();
}
