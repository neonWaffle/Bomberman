#pragma once
#include "Subject.h"
#include "TGUI/TGUI.hpp"

class TilemapEditorUI : public Subject
{
private:
	tgui::Panel::Ptr tileSelectionPanel;
	tgui::Panel::Ptr actionPanel;
	tgui::Panel::Ptr savePanel;
	tgui::ScrollablePanel::Ptr loadPanel;
	tgui::TextArea::Ptr fileNameInputArea;
	tgui::Label::Ptr invalidLoadMessage;
	tgui::Label::Ptr invalidSaveMessage;
	tgui::Label::Ptr validSaveMessage;
	void Save();
	void Load(const tgui::String& buttonText);
	void ToggleLoadPanel();
	void ShowSavedTilemaps();
public:
	TilemapEditorUI();
	void Open();
	void Close();
	bool MouseOnUI(sf::Vector2i mousePos);
};

