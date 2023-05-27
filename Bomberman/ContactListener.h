#pragma once

#include <b2_world_callbacks.h>
#include <b2_contact.h>
#include <b2_body.h>

class GameObject;

class ContactListener : public b2ContactListener
{
public:
    void BeginContact(b2Contact* contact) override;
    void EndContact(b2Contact* contact) override;
    bool IsOnSameTile(GameObject& objectA, GameObject& objectB);
};

