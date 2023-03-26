#pragma once
#include "glm/glm.hpp"
#include <SFML/Graphics.hpp>
#include <box2d/b2_math.h>
#include <box2d/b2_world.h>
#include <box2d/b2_body.h>

static class Converter
{
private:
	static float scale;
public:
	static float PhysicsToGraphics(float x);
	static float GraphicsToPhysics(float x);
};

