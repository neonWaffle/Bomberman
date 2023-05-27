#pragma once
#include "box2d.h"

class RaycastCallback : public b2RayCastCallback
{
private:
    b2Fixture* fixture;
    b2Vec2 point;
    b2Vec2 normal;
    float fraction;
public:
	RaycastCallback();

    float ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float fraction);
    b2Fixture* GetFixture();
};

