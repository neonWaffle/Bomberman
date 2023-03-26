#include "TilemapEditorUI.h"

void TilemapEditorUI::Save()
{
	if (TilemapManager::GetInstance()->Save(fileNameInputArea->getText().toStdString()))
	{
		invalidTilemapMessageSave->setVisible(false);
		validSaveMessage->setVisible(true);
	}
	else
	{
		invalidTilemapMessageSave->setVisible(true);
		validSaveMessage->setVisible(false);
	}
}

void TilemapEditorUI::Load(const tgui::String& buttonText)
{
	std::string filePath = "Assets/Levels/Custom/" + buttonText.toStdString() + ".map";
	if (TilemapManager::GetInstance()->EditTilemap(filePath))
		invalidTilemapMessageLoad->setVisible(false);
	else
		invalidTilemapMessageLoad->setVisible(true);
}

void TilemapEditorUI::OpenLoadPanel()
{
	savePanel->setVisible(false);
	loadPanel->setVisible(!loadPanel->isVisible());
	if (loadPanel->isVisible())
		ShowSavedTilemaps();
	else
		loadPanel->removeAllWidgets();
}

void TilemapEditorUI::ShowSavedTilemaps()
{
	tgui::Theme theme{ "Assets/Sprites/UI/theme.txt" };

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
			fileButton->setPosition(275, fileId * 40 + 20);
			fileButton->setSize(380, 50);
			fileButton->setOrigin(0.5f, 0.5f);
			fileButton->setText(fileName);
			fileButton->setTextSize(25);
			loadPanel->add(fileButton);
			fileButton->onPress([&](const tgui::String& buttonText) { Load(buttonText); });
			fileId++;
		}
	}
}

TilemapEditorUI::TilemapEditorUI()
{
	tgui::Theme theme{ "Assets/Sprites/UI/theme.txt" };

	editorPanel = tgui::Panel::create();
	editorPanel->setRenderer(theme.getRenderer("EditorPanel"));
	editorPanel->setOrigin(0.5f, 0.5f);
	editorPanel->setPosition(140, 50);
	editorPanel->setSize(270, 100);

	//General editor action UI:
	tgui::Button::Ptr returnButton = tgui::Button::create();
	returnButton->setRenderer(theme.getRenderer("MainMenuButton"));
	returnButton->setPosition(45, 50);
	returnButton->setSize(50, 50);
	returnButton->setOrigin(0.5f, 0.5f);
	returnButton->onPress([this]() { Notify(Event::OPEN_MAIN_MENU); });

	tgui::Button::Ptr saveButton = tgui::Button::create();
	saveButton->setRenderer(theme.getRenderer("SaveButton"));
	saveButton->setPosition(105, 50);
	saveButton->setSize(50, 50);
	saveButton->setOrigin(0.5f, 0.5f);
	saveButton->onPress([this]() 
		{
			loadPanel->setVisible(false);
			savePanel->setVisible(!savePanel->isVisible());
			validSaveMessage->setVisible(false);
		});

	tgui::Button::Ptr loadButton = tgui::Button::create();
	loadButton->setRenderer(theme.getRenderer("LoadButton"));
	loadButton->setPosition(165, 50);
	loadButton->setSize(50, 50);
	loadButton->setOrigin(0.5f, 0.5f);
	loadButton->onPress([this]() { OpenLoadPanel(); });

	tgui::Button::Ptr redoButton = tgui::Button::create();
	redoButton->setRenderer(theme.getRenderer("RedoButton"));
	redoButton->setPosition(225, 50);
	redoButton->setSize(50, 50);
	redoButton->setOrigin(0.5f, 0.5f);
	redoButton->onPress([this]() { TilemapManager::GetInstance()->ReloadTilemap(); });

	editorPanel->add(saveButton);
	editorPanel->add(redoButton);
	editorPanel->add(loadButton);
	editorPanel->add(returnButton);

	//Tile selection UI:
	tileSelectionPanel = tgui::Panel::create();
	tileSelectionPanel->setRenderer(theme.getRenderer("EditorPanelVertical"));
	tileSelectionPanel->setOrigin(0.5f, 0.5f);
	tileSelectionPanel->setPosition(130, 350);
	tileSelectionPanel->setSize(260, 600);

	tgui::Button::Ptr wallTileButton = tgui::Button::create();
	wallTileButton->setRenderer(theme.getRenderer("WallTileButton"));
	wallTileButton->setPosition(75, 130);
	wallTileButton->setSize(70, 70);
	wallTileButton->setOrigin(0.5f, 0.5f);
	wallTileButton->onPress([this]() { TilemapManager::GetInstance()->SelectTile(TileType::WALL); });

	tgui::Button::Ptr floorTileButton = tgui::Button::create();
	floorTileButton->setRenderer(theme.getRenderer("FloorTileButton"));
	floorTileButton->setPosition(185, 130);
	floorTileButton->setSize(70, 70);
	floorTileButton->setOrigin(0.5f, 0.5f);
	floorTileButton->onPress([this]() { TilemapManager::GetInstance()->SelectTile(TileType::FLOOR); });

	tgui::Button::Ptr boxTileButton = tgui::Button::create();
	boxTileButton->setRenderer(theme.getRenderer("BoxTileButton"));
	boxTileButton->setPosition(75, 230);
	boxTileButton->setSize(70, 70);
	boxTileButton->setOrigin(0.5f, 0.5f);
	boxTileButton->onPress([this]() { TilemapManager::GetInstance()->SelectTile(TileType::BOX); });

	tgui::Button::Ptr p1SpawnPointButton = tgui::Button::create();
	p1SpawnPointButton->setRenderer(theme.getRenderer("PlayerOneButton"));
	p1SpawnPointButton->setPosition(185, 230);
	p1SpawnPointButton->setSize(70, 70);
	p1SpawnPointButton->setOrigin(0.5f, 0.5f);
	p1SpawnPointButton->onPress([this]() { TilemapManager::GetInstance()->SelectTile(TileType::SPAWN_POINT_P1); });

	tgui::Button::Ptr p2SpawnPointButton = tgui::Button::create();
	p2SpawnPointButton->setRenderer(theme.getRenderer("PlayerTwoButton"));
	p2SpawnPointButton->setPosition(75, 330);
	p2SpawnPointButton->setSize(70, 70);
	p2SpawnPointButton->setOrigin(0.5f, 0.5f);
	p2SpawnPointButton->onPress([this]() { TilemapManager::GetInstance()->SelectTile(TileType::SPAWN_POINT_P2); });

	tileSelectionPanel->add(wallTileButton);
	tileSelectionPanel->add(floorTileButton);
	tileSelectionPanel->add(boxTileButton);
	tileSelectionPanel->add(p1SpawnPointButton);
	tileSelectionPanel->add(p2SpawnPointButton);

	//Tilemap load UI:
	loadPanel = tgui::ScrollablePanel::create();
	loadPanel->setRenderer(theme.getRenderer("ScrollablePanel"));
	loadPanel->setOrigin(0.5f, 0.5f);
	loadPanel->setPosition(450, 150);
	loadPanel->setSize(500, 250);
	loadPanel->setVerticalScrollbarPolicy(tgui::Scrollbar::Policy::Automatic);
	loadPanel->setHorizontalScrollbarPolicy(tgui::Scrollbar::Policy::Never);

	invalidTilemapMessageLoad = tgui::Label::create();
	invalidTilemapMessageLoad->setRenderer(theme.getRenderer("ErrorMessage"));
	invalidTilemapMessageLoad->setText("Invalid tilemap!");
	invalidTilemapMessageLoad->setTextSize(20);
	invalidTilemapMessageLoad->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Center);
	invalidTilemapMessageLoad->setPosition(360, 25);
	invalidTilemapMessageLoad->setSize(300, 50);
	invalidTilemapMessageLoad->setOrigin(0.5f, 0.5f);
	invalidTilemapMessageLoad->setVisible(false);

	//Tilemap save panel:
	savePanel = tgui::Panel::create();
	savePanel->setRenderer(theme.getRenderer("Panel"));
	savePanel->setOrigin(0.5f, 0.5f);
	savePanel->setPosition(430, 50);
	savePanel->setSize(370, 70);

	fileNameInputArea = tgui::TextArea::create();
	fileNameInputArea->setRenderer(theme.getRenderer("TextArea"));
	fileNameInputArea->setPosition(180, 40);
	fileNameInputArea->setSize(290, 35);
	fileNameInputArea->setTextSize(30);
	fileNameInputArea->setOrigin(0.5f, 0.5f);

	tgui::Button::Ptr confirmSaveButton = tgui::Button::create();
	confirmSaveButton->setRenderer(theme.getRenderer("SquareButton"));
	confirmSaveButton->setText("OK\n");
	confirmSaveButton->setTextSize(30);
	confirmSaveButton->setPosition(340, 35);
	confirmSaveButton->setSize(40, 40);
	confirmSaveButton->setOrigin(0.5f, 0.5f);
	confirmSaveButton->onPress([this]() { Save(); });

	invalidTilemapMessageSave = tgui::Label::create();
	invalidTilemapMessageSave->setRenderer(theme.getRenderer("ErrorMessage"));
	invalidTilemapMessageSave->setText("Invalid number of spawn points!");
	invalidTilemapMessageSave->setTextSize(20);
	invalidTilemapMessageSave->setPosition(185, 25);
	invalidTilemapMessageSave->setSize(300, 50);
	invalidTilemapMessageSave->setOrigin(0.5f, 0.5f);
	invalidTilemapMessageSave->setVisible(false);

	validSaveMessage = tgui::Label::create();
	validSaveMessage->setRenderer(theme.getRenderer("SuccessMessage"));
	validSaveMessage->setText("Saved!");
	validSaveMessage->setTextSize(20);
	validSaveMessage->setPosition(185, 25);
	validSaveMessage->setSize(300, 50);
	validSaveMessage->setOrigin(0.5f, 0.5f);
	validSaveMessage->setVisible(false);

	savePanel->add(fileNameInputArea);
	savePanel->add(confirmSaveButton);
	savePanel->add(invalidTilemapMessageSave);
	savePanel->add(validSaveMessage);

	loadPanel->setVisible(false);
	savePanel->setVisible(false);
}

void TilemapEditorUI::Open()
{
	EntityManager::GetInstance()->AddGUIElement(editorPanel);
	EntityManager::GetInstance()->AddGUIElement(tileSelectionPanel);
	EntityManager::GetInstance()->AddGUIElement(savePanel);
	EntityManager::GetInstance()->AddGUIElement(loadPanel);
	EntityManager::GetInstance()->AddGUIElement(invalidTilemapMessageLoad);
}

void TilemapEditorUI::Close()
{
	EntityManager::GetInstance()->RemoveGUIElement(editorPanel);
	EntityManager::GetInstance()->RemoveGUIElement(tileSelectionPanel);
	EntityManager::GetInstance()->RemoveGUIElement(savePanel);
	EntityManager::GetInstance()->RemoveGUIElement(loadPanel);
	EntityManager::GetInstance()->RemoveGUIElement(invalidTilemapMessageLoad);
}

bool TilemapEditorUI::MouseOnUI(sf::Vector2i mousePos)
{
	if (!loadPanel->isVisible())
		return false;
	auto pos = loadPanel->getPosition();
	auto upperBounds = pos + loadPanel->getSize() * 0.5f;
	auto lowerBounds = pos - loadPanel->getSize() * 0.5f;
	return mousePos.x >= lowerBounds.x && mousePos.x <= upperBounds.x && mousePos.y >= lowerBounds.y && mousePos.y <= upperBounds.y;
}
