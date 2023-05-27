#pragma once

class Converter
{
private:
	static float scale;
public:
	static float PhysicsToGraphics(float x);
	static float GraphicsToPhysics(float x);
};

