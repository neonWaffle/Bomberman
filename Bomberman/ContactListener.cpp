#include "ContactListener.h"

void ContactListener::BeginContact(b2Contact* contact)
{
    b2Body* bodyA = contact->GetFixtureA()->GetBody();
    b2Body* bodyB = contact->GetFixtureB()->GetBody();

    b2BodyUserData& bodyAData = bodyA->GetUserData();
    b2BodyUserData& bodyBData = bodyB->GetUserData();

    GameObject* objectA = reinterpret_cast<GameObject*>(bodyAData.pointer);
    GameObject* objectB = reinterpret_cast<GameObject*>(bodyBData.pointer);

    if (objectA->GetTag() == "Player")
    {
        if (objectB->GetTag() == "Explosion")
        {
            Player* player = dynamic_cast<Player*>(objectA);
            player->GetDamaged();
        }
        else if (objectB->GetTag() == "Pickup")
        {
            Pickup* pickup = dynamic_cast<Pickup*>(objectB);
            pickup->GetPickedUp(*dynamic_cast<Player*>(objectA));
        }
        else if (objectB->GetTag() == "EndTile" && IsOnSameTile(*objectA, *objectB))
        {
            Player* player = dynamic_cast<Player*>(objectA);
            player->GetKilled();
        }
    }
    else if (objectA->GetTag() == "Explosion")
    {
        if (objectB->GetTag() == "Player")
        {
            Player* player = dynamic_cast<Player*>(objectB);
            player->GetDamaged();
        }
        else if (objectB->GetTag() == "BoxTile")
        {
            BoxTile* box = dynamic_cast<BoxTile*>(objectB);
            box->GetDestroyed();
        }
        else if (objectB->GetTag() == "Bomb")
        {
            Bomb* bomb = dynamic_cast<Bomb*>(objectB);
            bomb->Explode();
        }
        else if (objectB->GetTag() == "EndTile")
        {
            EntityManager::GetInstance()->RemoveGameObject(objectA);
        }
    }
    else if (objectA->GetTag() == "Bomb")
    {
        if (objectB->GetTag() == "Explosion" && IsOnSameTile(*objectA, *objectB))
        {
            Bomb* bomb = dynamic_cast<Bomb*>(objectA);
            bomb->Explode();
        }
        else if (objectB->GetTag() == "EndTile" && IsOnSameTile(*objectA, *objectB))
        {
            Bomb* bomb = dynamic_cast<Bomb*>(objectA);
            bomb->Detonate();
        }
    }
    else if (objectA->GetTag() == "BoxTile")
    {
        if (objectB->GetTag() == "Explosion" && IsOnSameTile(*objectA, *objectB))
        {
            BoxTile* box = dynamic_cast<BoxTile*>(objectA);
            box->GetDestroyed();
        }
    }
    else if (objectA->GetTag() == "Pickup")
    {
        if (objectB->GetTag() == "Player")
        {
            Pickup* pickup = dynamic_cast<Pickup*>(objectA);
            pickup->GetPickedUp(*dynamic_cast<Player*>(objectB));
        }
        else if (objectB->GetTag() == "EndTile" && IsOnSameTile(*objectA, *objectB))
        {
            EntityManager::GetInstance()->RemoveGameObject(objectA);
        }
    }
    else if (objectA->GetTag() == "EndTile" && IsOnSameTile(*objectA, *objectB))
    {
        if (objectB->GetTag() == "Player")
        {
            Player* player = dynamic_cast<Player*>(objectB);
            player->GetKilled();
        }
        else if (objectB->GetTag() == "Bomb")
        {
            Bomb* bomb = dynamic_cast<Bomb*>(objectB);
            bomb->Detonate();
        }
        else if (objectB->GetTag() != "EndTile")
        {
            EntityManager::GetInstance()->RemoveGameObject(objectB);
        }
    }
}

void ContactListener::EndContact(b2Contact* contact)
{
}

bool ContactListener::IsOnSameTile(GameObject& objectA, GameObject& objectB)
{
    glm::vec2 objAPos = objectA.GetComponent<TransformComponent>()->GetPosition();
    glm::vec2 objBPos = objectB.GetComponent<TransformComponent>()->GetPosition();
    return std::abs(objAPos.x - objBPos.x) <= TilemapConfig::tileSize * 0.5f && std::abs(objAPos.y - objBPos.y) <= TilemapConfig::tileSize * 0.5f;
}
