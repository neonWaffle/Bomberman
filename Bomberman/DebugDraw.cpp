#include "DebugDraw.h"

DebugDraw::DebugDraw(std::shared_ptr<sf::RenderWindow> window)
{
    this->window = window;
    outlineThickness = 0.25f;
}

DebugDraw::~DebugDraw()
{
}

void DebugDraw::DrawPoint(const b2Vec2& p, float size, const b2Color& color)
{
}

void DebugDraw::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color)
{
}

void DebugDraw::DrawSolidCircle(const b2Vec2& center, float radius, const b2Vec2& axis, const b2Color& color)
{
    sf::CircleShape circle;
    circle.setOutlineThickness(outlineThickness);
    circle.setFillColor(sf::Color::Transparent);
    float rad = Converter::PhysicsToGraphics(radius);
    circle.setPosition(sf::Vector2f(Converter::PhysicsToGraphics(center.x), Converter::PhysicsToGraphics(center.y)));
    circle.setRadius(rad);
    circle.setOrigin(sf::Vector2f(rad, rad));
    window->draw(circle);
    b2Vec2 p = center + radius * axis;
    DrawSegment(center, p, color);
}

void DebugDraw::DrawCircle(const b2Vec2& center, float radius, const b2Color& color)
{
    sf::CircleShape circle;
    circle.setOutlineThickness(outlineThickness);
    circle.setFillColor(sf::Color::Transparent);
    float rad = Converter::PhysicsToGraphics(radius);
    circle.setPosition(sf::Vector2f(Converter::PhysicsToGraphics(center.x), Converter::PhysicsToGraphics(center.y)));
    circle.setRadius(rad);
    circle.setOrigin(sf::Vector2f(rad, rad));
    window->draw(circle);
}

void DebugDraw::DrawTransform(const b2Transform& xf)
{
}

void DebugDraw::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
    sf::ConvexShape polygon;
    polygon.setOutlineThickness(outlineThickness);
    polygon.setFillColor(sf::Color::Transparent);
    polygon.setPointCount(vertexCount);
    for (int32 i = 0; i < vertexCount; i++)
        polygon.setPoint(i, sf::Vector2f(Converter::PhysicsToGraphics(vertices[i].x), Converter::PhysicsToGraphics(vertices[i].y)));
    window->draw(polygon);
}

void DebugDraw::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
    sf::ConvexShape polygon;
    polygon.setOutlineThickness(outlineThickness);
    polygon.setFillColor(sf::Color::Transparent);
    polygon.setPointCount(vertexCount);
    for (int32 i = 0; i < vertexCount; i++)
        polygon.setPoint(i, sf::Vector2f(Converter::PhysicsToGraphics(vertices[i].x), Converter::PhysicsToGraphics(vertices[i].y)));
    window->draw(polygon);
}
