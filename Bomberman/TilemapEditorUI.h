#pragma once
#include "EntityManager.h"
#include "TilemapManager.h"
#include "InputHandler.h"
#include "TGUI/TGUI.hpp"
#include <filesystem>

class TilemapEditorUI : public Subject
{
private:
	tgui::Panel::Ptr tileSelectionPanel;
	tgui::Panel::Ptr editorPanel;
	tgui::Panel::Ptr savePanel;
	tgui::ScrollablePanel::Ptr loadPanel;
	tgui::TextArea::Ptr fileNameInputArea;
	tgui::Label::Ptr invalidTilemapMessageLoad;
	tgui::Label::Ptr invalidTilemapMessageSave;
	tgui::Label::Ptr validSaveMessage;
	void Save();
	void Load(const tgui::String& buttonText);
	void OpenLoadPanel();
	void ShowSavedTilemaps();
public:
	TilemapEditorUI();
	void Open();
	void Close();
	bool MouseOnUI(sf::Vector2i mousePos);
};

