#pragma once

#include "Subject.h"

#include <TGUI/TGUI.hpp>

class MainMenu : public Subject
{
private:
	tgui::Panel::Ptr mainMenuPanel;
	tgui::Panel::Ptr customLevelSelectionPanel;
	tgui::ScrollablePanel::Ptr filePanel;
	tgui::Label::Ptr invalidTilemapMessage;

	void OpenCustomLevelPanel();
	void LoadCustomLevel(const tgui::String& buttonText);
	void OpenMainMenuPanel();
public:
	MainMenu();
	~MainMenu();

	void Open();
	void Close();
};

