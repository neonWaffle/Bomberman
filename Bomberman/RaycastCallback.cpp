#include "RaycastCallback.h"

RaycastCallback::RaycastCallback()
{
}

float RaycastCallback::ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float fraction)
{
    this->fixture = fixture;
    this->point = point;
    this->normal = normal;
    this->fraction = fraction;
    return fraction;
}

b2Fixture* RaycastCallback::GetFixture()
{
    return fixture;
}
