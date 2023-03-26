#include "GraphicsSubsystem.h"

GraphicsSubsystem::GraphicsSubsystem(std::shared_ptr<sf::RenderWindow> window)
{
    this->window = window;
}

void GraphicsSubsystem::Init()
{
    gui = std::make_unique<tgui::GuiSFML>();
    gui->setTarget(*window);
    gui->setFont("Assets/Fonts/visitor/visitor2.ttf");
}

void GraphicsSubsystem::Update(float deltaTime)
{
    sf::Event event;
    while (window->pollEvent(event))
    {
        gui->handleEvent(event);
        if (event.type == sf::Event::Closed)
            window->close();
    }
    window->clear();
    for (auto&& obj : EntityManager::GetInstance()->gameObjects)
    {
        auto* graphicsComponent = obj->GetComponent<GraphicsComponent>();
        auto* transformComponent = obj->GetComponent<TransformComponent>();
        window->draw(*graphicsComponent->GetSprite(transformComponent->GetPosition(), deltaTime));
    }
    gui->draw();
    window->display();
}

void GraphicsSubsystem::Close()
{
    window->close();
}

void GraphicsSubsystem::OnNotify(Event event, tgui::Widget::Ptr guiElement)
{
    switch (event)
    {
    case Event::GUI_ELEMENT_ADDED:
        gui->add(guiElement);
        break;
    case Event::GUI_ELEMENT_REMOVED:
        gui->remove(guiElement);
        break;
    }
}
