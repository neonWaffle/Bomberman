#pragma once
#include "Subsystem.h"
#include <SFML/Graphics.hpp>

class GraphicsSubsystem : public Subsystem
{
private:
	std::shared_ptr<sf::RenderWindow> window;
	std::shared_ptr<glm::vec2> position;
	std::unique_ptr<tgui::GuiSFML> gui;
	std::vector<tgui::Widget::Ptr> guiElements;
public:
	GraphicsSubsystem(std::shared_ptr<sf::RenderWindow> window);
	void Init() override;
	void Update(float deltaTime) override;
	void Close() override;
	void OnNotify(Event event, tgui::Widget::Ptr guiElement);
};

