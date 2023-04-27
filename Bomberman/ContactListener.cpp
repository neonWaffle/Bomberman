#include "ContactListener.h"
#include "BoxTile.h"
#include "Pickup.h"
#include "Bomb.h"
#include "Player.h"
#include "EntityManager.h"
#include "TransformComponent.h"
#include "TilemapConfig.h"

void ContactListener::BeginContact(b2Contact* contact)
{
    b2Body* bodyA = contact->GetFixtureA()->GetBody();
    b2Body* bodyB = contact->GetFixtureB()->GetBody();

    b2BodyUserData& bodyAData = bodyA->GetUserData();
    b2BodyUserData& bodyBData = bodyB->GetUserData();

    GameObject* objectA = reinterpret_cast<GameObject*>(bodyAData.pointer);
    GameObject* objectB = reinterpret_cast<GameObject*>(bodyBData.pointer);

    std::string objectATag = objectA->GetTag();
    std::string objectBTag = objectB->GetTag();

    if (objectATag == "Player")
    {
        if (objectBTag == "Explosion")
        {
            Player* player = dynamic_cast<Player*>(objectA);
            player->GetDamaged();
        }
        else if (objectBTag == "Pickup")
        {
            Pickup* pickup = dynamic_cast<Pickup*>(objectB);
            pickup->GetPickedUp(*dynamic_cast<Player*>(objectA));
        }
        else if (objectBTag == "EndTile" && IsOnSameTile(*objectA, *objectB))
        {
            Player* player = dynamic_cast<Player*>(objectA);
            player->GetKilled();
        }
    }
    else if (objectATag == "Explosion")
    {
        if (objectBTag == "Player")
        {
            Player* player = dynamic_cast<Player*>(objectB);
            player->GetDamaged();
        }
        else if (objectBTag == "BoxTile")
        {
            BoxTile* box = dynamic_cast<BoxTile*>(objectB);
            box->GetDestroyed();
        }
        else if (objectBTag == "Bomb")
        {
            Bomb* bomb = dynamic_cast<Bomb*>(objectB);
            bomb->Explode();
        }
        else if (objectBTag == "EndTile")
        {
            EntityManager::GetInstance()->RemoveGameObject(objectA);
        }
    }
    else if (objectATag == "Bomb")
    {
        if (objectBTag == "Explosion" && IsOnSameTile(*objectA, *objectB))
        {
            Bomb* bomb = dynamic_cast<Bomb*>(objectA);
            bomb->Explode();
        }
        else if (objectBTag == "EndTile" && IsOnSameTile(*objectA, *objectB))
        {
            Bomb* bomb = dynamic_cast<Bomb*>(objectA);
            bomb->Detonate();
        }
    }
    else if (objectATag == "BoxTile")
    {
        if (objectBTag == "Explosion" && IsOnSameTile(*objectA, *objectB))
        {
            BoxTile* box = dynamic_cast<BoxTile*>(objectA);
            box->GetDestroyed();
        }
    }
    else if (objectATag == "Pickup")
    {
        if (objectBTag == "Player")
        {
            Pickup* pickup = dynamic_cast<Pickup*>(objectA);
            pickup->GetPickedUp(*dynamic_cast<Player*>(objectB));
        }
        else if (objectBTag == "EndTile" && IsOnSameTile(*objectA, *objectB))
        {
            EntityManager::GetInstance()->RemoveGameObject(objectA);
        }
    }
    else if (objectATag == "EndTile" && IsOnSameTile(*objectA, *objectB))
    {
        if (objectBTag == "Player")
        {
            Player* player = dynamic_cast<Player*>(objectB);
            player->GetKilled();
        }
        else if (objectBTag == "Bomb")
        {
            Bomb* bomb = dynamic_cast<Bomb*>(objectB);
            bomb->Detonate();
        }
        else if (objectBTag != "EndTile")
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
