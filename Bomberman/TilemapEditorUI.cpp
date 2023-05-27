#include "TilemapEditorUI.h"

#include "EntityManager.h"
#include "TilemapManager.h"
#include "InputHandler.h"

#include <filesystem>

void TilemapEditorUI::Save()
{
	if (TilemapManager::GetInstance()->Save(fileNameInputArea->getText().toStdString()))
	{
		invalidSaveMessage->setVisible(false);
		validSaveMessage->setVisible(true);
	}
	else
	{
		invalidSaveMessage->setVisible(true);
		validSaveMessage->setVisible(false);
	}
}

void TilemapEditorUI::Load(const tgui::String& buttonText)
{
	std::string filePath = "Assets/Levels/Custom/" + buttonText.toStdString() + ".map";
	if (TilemapManager::GetInstance()->EditTilemap(filePath))
	{
		invalidLoadMessage->setVisible(false);
	}
	else
	{
		invalidLoadMessage->setVisible(true);
	}
}

void TilemapEditorUI::ToggleLoadPanel()
{
	savePanel->setVisible(false);
	loadPanel->setVisible(!loadPanel->isVisible());
	if (loadPanel->isVisible())
	{
		ShowSavedTilemaps();
	}
	else
	{
		loadPanel->removeAllWidgets();
	}
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

			auto fileButton = tgui::Button::create();
			fileButton->setRenderer(theme.getRenderer("FileButton"));
			fileButton->setPosition(0.0f, tgui::Layout("25%") * fileId);
			fileButton->setSize("100%", "25%");
			fileButton->setText(fileName);
			fileButton->setTextSize(25);
			fileButton->onPress([&](const tgui::String& buttonText) { Load(buttonText); });

			loadPanel->add(fileButton);

			fileId++;
		}
	}
}

TilemapEditorUI::TilemapEditorUI()
{
	tgui::Theme theme{ "Assets/Sprites/UI/theme.txt" };

	actionPanel = tgui::Panel::create();
	actionPanel->setRenderer(theme.getRenderer("EditorPanel"));
	actionPanel->setPosition(0.0f, 0.0f);
	actionPanel->setSize("15%", "8%");

	//Editor action UI:
	auto returnButton = tgui::Button::create();
	returnButton->setRenderer(theme.getRenderer("MainMenuButton"));
	returnButton->setPosition("15%", "50%");
	returnButton->setSize("parent.height * 0.5", "parent.height * 0.5");
	returnButton->setOrigin(0.5f, 0.5f);
	returnButton->onPress([this]() { Notify(Event::OPEN_MAIN_MENU); });

	actionPanel->add(returnButton);

	auto saveButton = tgui::Button::create();
	saveButton->setRenderer(theme.getRenderer("SaveButton"));
	saveButton->setPosition("35%", "50%");
	saveButton->setSize("parent.height * 0.5", "parent.height * 0.5");
	saveButton->setOrigin(0.5f, 0.5f);
	saveButton->onPress([this]() 
		{
			loadPanel->setVisible(false);
			savePanel->setVisible(!savePanel->isVisible());
			validSaveMessage->setVisible(false);
		});

	actionPanel->add(saveButton);

	auto loadButton = tgui::Button::create();
	loadButton->setRenderer(theme.getRenderer("LoadButton"));
	loadButton->setPosition("55%", "50%");
	loadButton->setSize("parent.height * 0.5", "parent.height * 0.5");
	loadButton->setOrigin(0.5f, 0.5f);
	loadButton->onPress([this]() { ToggleLoadPanel(); });

	actionPanel->add(loadButton);

	auto redoButton = tgui::Button::create();
	redoButton->setRenderer(theme.getRenderer("RedoButton"));
	redoButton->setPosition("75%", "50%");
	redoButton->setSize("parent.height * 0.5", "parent.height * 0.5");
	redoButton->setOrigin(0.5f, 0.5f);
	redoButton->onPress([this]() { TilemapManager::GetInstance()->ReloadTilemap(); });

	actionPanel->add(redoButton);

	//Tile selection UI:
	tileSelectionPanel = tgui::Panel::create();
	tileSelectionPanel->setRenderer(theme.getRenderer("EditorPanelVertical"));
	tileSelectionPanel->setSize("15%", "40%");
	tileSelectionPanel->setPosition({ tgui::bindLeft(actionPanel), tgui::bindBottom(actionPanel) });

	auto wallTileButton = tgui::Button::create();
	wallTileButton->setRenderer(theme.getRenderer("WallTileButton"));
	wallTileButton->setPosition("parent.width * 0.25", "parent.width * 0.25");
	wallTileButton->setSize("parent.width * 0.25", "parent.width * 0.25");
	wallTileButton->setOrigin(0.5f, 0.5f);
	wallTileButton->onPress([this]() { TilemapManager::GetInstance()->SelectTile(TileType::WALL); });

	tileSelectionPanel->add(wallTileButton);

	auto floorTileButton = tgui::Button::create();
	floorTileButton->setRenderer(theme.getRenderer("FloorTileButton"));
	floorTileButton->setPosition("parent.width * 0.75", "parent.width * 0.25");
	floorTileButton->setSize("parent.width * 0.25", "parent.width * 0.25");
	floorTileButton->setOrigin(0.5f, 0.5f);
	floorTileButton->onPress([this]() { TilemapManager::GetInstance()->SelectTile(TileType::FLOOR); });

	tileSelectionPanel->add(floorTileButton);

	auto boxTileButton = tgui::Button::create();
	boxTileButton->setRenderer(theme.getRenderer("BoxTileButton"));
	boxTileButton->setPosition("parent.width * 0.25", "parent.width * 0.75");
	boxTileButton->setSize("parent.width * 0.25", "parent.width * 0.25");
	boxTileButton->setOrigin(0.5f, 0.5f);
	boxTileButton->onPress([this]() { TilemapManager::GetInstance()->SelectTile(TileType::BOX); });

	tileSelectionPanel->add(boxTileButton);

	auto p1SpawnPointButton = tgui::Button::create();
	p1SpawnPointButton->setRenderer(theme.getRenderer("PlayerOneButton"));
	p1SpawnPointButton->setPosition("parent.width * 0.75", "parent.width * 0.75");
	p1SpawnPointButton->setSize("parent.width * 0.25", "parent.width * 0.25");
	p1SpawnPointButton->setOrigin(0.5f, 0.5f);
	p1SpawnPointButton->onPress([this]() { TilemapManager::GetInstance()->SelectTile(TileType::SPAWN_POINT_P1); });

	tileSelectionPanel->add(p1SpawnPointButton);

	auto p2SpawnPointButton = tgui::Button::create();
	p2SpawnPointButton->setRenderer(theme.getRenderer("PlayerTwoButton"));
	p2SpawnPointButton->setPosition("parent.width * 0.25", "parent.width * 1.25");
	p2SpawnPointButton->setSize("parent.width * 0.25", "parent.width * 0.25");
	p2SpawnPointButton->setOrigin(0.5f, 0.5f);
	p2SpawnPointButton->onPress([this]() { TilemapManager::GetInstance()->SelectTile(TileType::SPAWN_POINT_P2); });

	tileSelectionPanel->add(p2SpawnPointButton);

	//Tilemap load UI:
	loadPanel = tgui::ScrollablePanel::create();
	loadPanel->setRenderer(theme.getRenderer("ScrollablePanel"));
	loadPanel->setPosition({ tgui::bindRight(actionPanel), tgui::bindTop(actionPanel) });
	loadPanel->setSize("25%", "15%");
	loadPanel->setVerticalScrollbarPolicy(tgui::Scrollbar::Policy::Automatic);
	loadPanel->setHorizontalScrollbarPolicy(tgui::Scrollbar::Policy::Never);

	invalidLoadMessage = tgui::Label::create();
	invalidLoadMessage->setRenderer(theme.getRenderer("ErrorMessage"));
	invalidLoadMessage->setText("Invalid tilemap!");
	invalidLoadMessage->setTextSize(20);
	invalidLoadMessage->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Left);
	invalidLoadMessage->setPosition({ tgui::bindLeft(loadPanel), tgui::bindBottom(loadPanel) });
	invalidLoadMessage->setSize("20%", "5%");
	invalidLoadMessage->setVisible(false);

	//Tilemap save panel:
	savePanel = tgui::Panel::create();
	savePanel->setRenderer(theme.getRenderer("Panel"));
	savePanel->setPosition({ tgui::bindRight(actionPanel), tgui::bindTop(actionPanel) });
	savePanel->setSize("20%", "5%");

	fileNameInputArea = tgui::TextArea::create();
	fileNameInputArea->setRenderer(theme.getRenderer("TextArea"));
	fileNameInputArea->setOrigin(0.0f, 0.5f);
	fileNameInputArea->setPosition("2%", "50%");
	fileNameInputArea->setSize("85%", "70%");
	fileNameInputArea->setTextSize(30);

	savePanel->add(fileNameInputArea);

	auto confirmSaveButton = tgui::Button::create();
	confirmSaveButton->setRenderer(theme.getRenderer("SquareButton"));
	confirmSaveButton->setText("OK\n");
	confirmSaveButton->setOrigin(0.0f, 0.5f);
	confirmSaveButton->setPosition("85%", "50%");
	confirmSaveButton->setSize("parent.height * 0.9f", "parent.height * 0.9f");
	confirmSaveButton->setTextSize(30);
	confirmSaveButton->onPress([this]() { Save(); });

	savePanel->add(confirmSaveButton);

	invalidSaveMessage = tgui::Label::create();
	invalidSaveMessage->setRenderer(theme.getRenderer("ErrorMessage"));
	invalidSaveMessage->setText("Invalid number of spawn points!");
	invalidSaveMessage->setTextSize(20);
	invalidSaveMessage->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Left);
	invalidSaveMessage->setPosition("2%", "2%");
	invalidSaveMessage->setSize("100%", "45%");
	invalidSaveMessage->setVisible(false);

	savePanel->add(invalidSaveMessage);

	validSaveMessage = tgui::Label::create();
	validSaveMessage->setRenderer(theme.getRenderer("SuccessMessage"));
	validSaveMessage->setText("Saved!");
	validSaveMessage->setTextSize(20);
	validSaveMessage->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Left);
	validSaveMessage->setPosition("2%", "2%");
	validSaveMessage->setSize("100%", "45%");
	validSaveMessage->setVisible(false);

	savePanel->add(validSaveMessage);

	loadPanel->setVisible(false);
	savePanel->setVisible(false);
}

void TilemapEditorUI::Open()
{
	EntityManager::GetInstance()->AddGUIElement(actionPanel);
	EntityManager::GetInstance()->AddGUIElement(tileSelectionPanel);
	EntityManager::GetInstance()->AddGUIElement(savePanel);
	EntityManager::GetInstance()->AddGUIElement(loadPanel);
	EntityManager::GetInstance()->AddGUIElement(invalidLoadMessage);
}

void TilemapEditorUI::Close()
{
	EntityManager::GetInstance()->RemoveGUIElement(actionPanel);
	EntityManager::GetInstance()->RemoveGUIElement(tileSelectionPanel);
	EntityManager::GetInstance()->RemoveGUIElement(savePanel);
	EntityManager::GetInstance()->RemoveGUIElement(loadPanel);
	EntityManager::GetInstance()->RemoveGUIElement(invalidLoadMessage);
}

bool TilemapEditorUI::MouseOnUI(sf::Vector2i mousePos)
{
	if (!loadPanel->isVisible())
	{
		return false;
	}

	auto pos = loadPanel->getPosition();
	auto upperBounds = pos + loadPanel->getSize() * 0.5f;
	auto lowerBounds = pos - loadPanel->getSize() * 0.5f;
	return mousePos.x >= lowerBounds.x && mousePos.x <= upperBounds.x && mousePos.y >= lowerBounds.y && mousePos.y <= upperBounds.y;
}
