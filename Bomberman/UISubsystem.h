#pragma once
#include "Subsystem.h"
#include "GUIElement.h"
#include <TGUI/TGUI.hpp>

class UISubsystem : public Subsystem
{
private:
	std::shared_ptr<sf::RenderWindow> window;
	std::unique_ptr<tgui::GuiSFML> gui;
	std::vector<tgui::Widget::Ptr> guiElements;
public:
	UISubsystem(std::shared_ptr<sf::RenderWindow> window);
	void Update(float deltaTime) override;
	void OnNotify(Event event, tgui::Widget::Ptr guiElement);
};

