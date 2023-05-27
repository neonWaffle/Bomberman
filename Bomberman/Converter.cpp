#include "Converter.h"

float Converter::scale = 32.0f;

float Converter::PhysicsToGraphics(float x)
{
    return x * scale;
}

float Converter::GraphicsToPhysics(float x)
{
    return x / scale;
}
