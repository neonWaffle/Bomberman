#include "MainMenu.h"

void MainMenu::OpenCustomLevelPanel()
{
	tgui::Theme theme{ "Assets/Sprites/UI/theme.txt" };
	mainMenuPanel->setVisible(false);
	customLevelSelectionPanel->setVisible(true);
}

void MainMenu::LoadCustomLevel(const tgui::String& buttonText)
{
	if (!TilemapManager::GetInstance()->PlayCustomTilemap(buttonText.toStdString()))
		invalidTilemapMessage->setVisible(true);
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
	mainMenuPanel->setOrigin(0.5f, 0.5f);
	mainMenuPanel->setPosition("50%", "50%");
	mainMenuPanel->setSize(TilemapConfig::screenWidth, TilemapConfig::screenHeight);

	tgui::Label::Ptr titleText = tgui::Label::create();
	titleText->setRenderer(theme.getRenderer("Label"));
	titleText->setText("Bomberman");
	titleText->setPosition("50%", "30%");
	titleText->setSize(450, 150);
	titleText->setTextSize(100);
	titleText->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Center);
	titleText->setOrigin(0.5f, 0.5f);

	tgui::Button::Ptr startButton = tgui::Button::create("Start\n");
	startButton->setRenderer(theme.getRenderer("Button"));
	startButton->setPosition("50%", "50%");
	startButton->setSize(200, 70);
	startButton->setTextSize(30);
	startButton->setOrigin(0.5f, 0.5f);
	startButton->onPress([this]() { TilemapManager::GetInstance()->PlayDefaultTilemap(); });

	tgui::Button::Ptr customLevelButton = tgui::Button::create("Load custom\n");
	customLevelButton->setRenderer(theme.getRenderer("Button"));
	customLevelButton->setPosition("50%", "55%");
	customLevelButton->setSize(200, 70);
	customLevelButton->setTextSize(30);
	customLevelButton->setOrigin(0.5f, 0.5f);
	customLevelButton->onPress([this]() { OpenCustomLevelPanel(); });

	tgui::Button::Ptr editorButton = tgui::Button::create("Map editor\n");
	editorButton->setRenderer(theme.getRenderer("Button"));
	editorButton->setPosition("50%", "60%");
	editorButton->setSize(200, 70);
	editorButton->setTextSize(30);
	editorButton->setOrigin(0.5f, 0.5f);
	editorButton->onPress([this]() { TilemapManager::GetInstance()->OpenEditor(); });

	tgui::Button::Ptr exitButton = tgui::Button::create("Exit\n");
	exitButton->setRenderer(theme.getRenderer("Button"));
	exitButton->setPosition("50%", "65%");
	exitButton->setSize(200, 70);
	exitButton->setTextSize(30);
	exitButton->setOrigin(0.5f, 0.5f);
	exitButton->onPress([this]() { Notify(Event::EXIT_GAME); });

	mainMenuPanel->add(titleText);
	mainMenuPanel->add(startButton);
	mainMenuPanel->add(customLevelButton);
	mainMenuPanel->add(editorButton);
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
	filePanel->setSize(490, 520);
	filePanel->setVerticalScrollbarPolicy(tgui::Scrollbar::Policy::Always);
	filePanel->setHorizontalScrollbarPolicy(tgui::Scrollbar::Policy::Never);

	customLevelSelectionPanel->add(filePanel);

	tgui::Label::Ptr customLevelSelectionTitle = tgui::Label::create("Custom levels");
	customLevelSelectionTitle->setRenderer(theme.getRenderer("Label"));
	customLevelSelectionTitle->setPosition("50%", "30%");
	customLevelSelectionTitle->setSize(470, 150);
	customLevelSelectionTitle->setTextSize(70);
	customLevelSelectionTitle->setOrigin(0.5f, 0.5f);
	customLevelSelectionTitle->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Center);
	customLevelSelectionPanel->add(customLevelSelectionTitle);

	std::string path = "Assets/Levels/Custom";
	int fileId = 0;
	int buttonOffset = 20;
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
			fileButton->setPosition("48%", fileId * 50 + buttonOffset);
			fileButton->setSize(470, 50);
			fileButton->setOrigin(0.5f, 0.5f);
			fileButton->setText(fileName);
			fileButton->setTextSize(25);
			filePanel->add(fileButton);
			fileButton->onPress([&](const tgui::String& buttonText) { LoadCustomLevel(buttonText); });
			fileId++;
		}
	}

	tgui::Button::Ptr returnButton = tgui::Button::create();
	returnButton->setRenderer(theme.getRenderer("ReturnButton"));
	returnButton->setPosition(100, 100);
	returnButton->setSize(50, 50);
	returnButton->setTextSize(30);
	returnButton->setOrigin(0.5f, 0.5f);
	returnButton->onPress([this]() { OpenMainMenuPanel(); });
	customLevelSelectionPanel->add(returnButton);

	invalidTilemapMessage = tgui::Label::create();
	invalidTilemapMessage->setRenderer(theme.getRenderer("ErrorMessage"));
	invalidTilemapMessage->setText("Invalid tilemap!");
	invalidTilemapMessage->setTextSize(20);
	invalidTilemapMessage->setPosition(1185, 1080);
	invalidTilemapMessage->setSize(300, 50);
	invalidTilemapMessage->setOrigin(0.5f, 0.5f);
	invalidTilemapMessage->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Left);
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
