#pragma once
#include "Subject.h"
#include "EntityManager.h"
#include "TilemapManager.h"
#include <TGUI/TGUI.hpp>

class GameOverScreen : public Subject
{
private:
	tgui::Panel::Ptr gameOverPanel;
public:
	void Open(int winnerId);
	void Close();
};

