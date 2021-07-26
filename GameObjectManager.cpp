#include <SFML/Graphics.hpp>
#include "GameObjectManager.h"

GameObjectManager::GameObjectManager()
{}

GameObjectManager::~GameObjectManager()
{
    Clear();
}

void GameObjectManager::Add(GameObject* gameObject)
{
    gameObjects_.push_back(gameObject);
}

void GameObjectManager::Update(float delta_time)
{
    for (auto gameObject : gameObjects_)
    {
        gameObject->Update(delta_time);
    }
}

void GameObjectManager::DelayedUpdate(float delta_time)
{
    for (auto gameObject : gameObjects_)
    {
        gameObject->DelayedUpdate(delta_time);
    }
}

void GameObjectManager::Draw(Camera& camera) const
{
    for (auto gameObject : gameObjects_)
    {
        gameObject->Draw(camera);
    }
}

void GameObjectManager::DelayedDraw(Camera& camera) const
{
    for (auto gameObject : gameObjects_)
    {
        gameObject->DelayedDraw(camera);
    }
}

void GameObjectManager::Collision()
{
    for (auto i = gameObjects_.begin(); i != gameObjects_.end(); i++)
    {
        if (!(*i)->GetActive()) continue; //skips if gameobject is not active
        for (auto j = next(i); j != gameObjects_.end(); j++)
        {
            if (!(*j)->GetActive()) continue;
            if ((*i)->IsCollision(**j)) (*i)->OnCollision(**j);
        }
    }
}

void GameObjectManager::ReverseCollision()
{
    for (auto i = --gameObjects_.end(); i != --gameObjects_.begin(); i--)
    {
        if (!(*i)->GetActive()) continue;
        for (auto j = prev(i); j != --gameObjects_.begin(); j--)
        {
            if (!(*j)->GetActive()) continue;
            if ((*i)->IsCollision(**j)) (*i)->OnCollision(**j);
        }
    }
}

void GameObjectManager::OneWayCollision()
{
    for (auto i = gameObjects_.begin(); i != gameObjects_.end(); i++)
    {
        if (!(*i)->GetActive()) continue;
        for (auto j = gameObjects_.begin(); j != gameObjects_.end(); j++)
        {
            if (i == j) continue;
            if (!(*j)->GetActive()) continue;
            if ((*i)->IsCollision(**j)) (*i)->OnOneWayCollision(**j);
        }
    }
}

void GameObjectManager::OneWayReverseCollision()
{
    for (auto i = --gameObjects_.end(); i != --gameObjects_.begin(); i--)
    {
        if (!(*i)->GetActive()) continue;
        for (auto j = --gameObjects_.end(); j != --gameObjects_.begin(); j--)
        {
            if (i == j) continue;
            if (!(*j)->GetActive()) continue;
            if ((*i)->IsCollision(**j)) (*i)->OnOneWayCollision(**j);
        }
    }
}

void GameObjectManager::Interaction()
{
    for (auto i = gameObjects_.begin(); i != gameObjects_.end(); i++)
    {
        if (!(*i)->GetActive()) continue;
        for (auto j = next(i); j != gameObjects_.end(); j++)
        {
            if (!(*j)->GetActive()) continue;
            if ((*i)->IsCollision(**j)) (*i)->OnCollision(**j);
            else (*i)->OnMissedCollision(**j);
        }
    }
}


void GameObjectManager::ReverseInteraction()
{
    for (auto i = --gameObjects_.end(); i != --gameObjects_.begin(); i--)
    {
        if (!(*i)->GetActive()) continue;
        for (auto j = prev(i); j != --gameObjects_.begin(); j--)
        {
            if (!(*j)->GetActive()) continue;
            if ((*i)->IsCollision(**j)) (*i)->OnCollision(**j);
            else (*i)->OnMissedCollision(**j);
        }
    }
}

void GameObjectManager::OneWayInteraction()
{
    for (auto i = gameObjects_.begin(); i != gameObjects_.end(); i++)
    {
        if (!(*i)->GetActive()) continue;
        for (auto j = gameObjects_.begin(); j != gameObjects_.end(); j++)
        {
            if (i == j) continue;
            if (!(*j)->GetActive()) continue;
            if ((*i)->IsCollision(**j)) (*i)->OnOneWayCollision(**j);
            else (*i)->OnMissedOneWayCollision(**j);
        }
    }
}

void GameObjectManager::OneWayReverseInteraction()
{
    for (auto i = --gameObjects_.end(); i != --gameObjects_.begin(); i--)
    {
        if (!(*i)->GetActive()) continue;
        for (auto j = --gameObjects_.end(); j != --gameObjects_.begin(); j--)
        {
            if (i == j) continue;
            if (!(*j)->GetActive()) continue;
            if ((*i)->IsCollision(**j)) (*i)->OnOneWayCollision(**j);
            else (*i)->OnMissedOneWayCollision(**j);
        }
    }
}

void GameObjectManager::Remove()
{
    for (auto i = gameObjects_.begin(); i != gameObjects_.end(); )
    {
        if ((*i)->IsDead() && (*i)->GetTag() != "Player")
        {
            delete *i;
            i = gameObjects_.erase(i);
        }
        else i++;
    }
}

GameObject* GameObjectManager::Find(const std::string& string, const bool byName, const bool byTag, const bool byID)
{
    if (byName)
    {
        return FindByName(string);
    }
    else if (byTag)
    {
        return FindByTag(string);
    }
    else if (byID)
    {
        return FindByID(std::stoi(string));
    }
    return nullptr;
}

GameObject* GameObjectManager::FindByName(const std::string& string) const
{
    for (auto gameObject : gameObjects_)
    {
        if (gameObject->GetName() == string) return gameObject;
    }
    return nullptr;
}

GameObject* GameObjectManager::FindByTag(const std::string& string) const
{
    for (auto gameObject : gameObjects_)
    {
        if (gameObject->GetTag() == string) return gameObject;
    }
    return nullptr;
}

GameObject* GameObjectManager::FindByID(const int ID) const
{
    for (auto gameObject : gameObjects_)
    {
        if (gameObject->GetID() == ID)
        {
            return gameObject;
        }
    }
    return nullptr;
}

void GameObjectManager::SortByLayers()
{
    gameObjects_.sort( [](GameObject* a, GameObject* b) {return a->GetLayerID() < b->GetLayerID();} );
}

void GameObjectManager::Clear()
{
    for (auto gameObject : gameObjects_)
    {
        delete gameObject;
    }
    gameObjects_.clear();
}