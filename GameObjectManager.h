#ifndef GAMEOBJECT_MANAGER_H_
#define GAMEOBJECT_MANAGER_H_
#include <list>
#include "GameObject.h"
#include "Camera.h"

class GameObjectManager
{
public:
    GameObjectManager();
    ~GameObjectManager();
    //Add a gameobject to the list of gameobjects
    void Add(GameObject* gameObject);
    //Update all gameobjects in the list
    void Update(float delta_time);
    //Same as Update, call after Update
    void DelayedUpdate(float delta_time);
    //Draw all gameobjects in the list
    void Draw(Camera& camera) const;
    //Same as Draw, call after Draw
    void DelayedDraw(Camera& camera) const;
    //Checks ONLY collision between gameobjects
    void Collision();
    //Checks collision between gameobjects but starts from the last created object
    void ReverseCollision();
    //More intensive but more accurate
    //Checks if "A" collides with "B" and if "B" collides with "A"
    void OneWayCollision();
    //Same as above but starts at last created object
    void OneWayReverseCollision();
    //Checks for collisions and non-collisions
    void Interaction();
    void ReverseInteraction();
    void OneWayInteraction();
    void OneWayReverseInteraction();
    //Remove "dead" gameobjects
    void Remove();
    //Find a GameObject
    GameObject* Find(const std::string& string, const bool byName = true, const bool byTag = false, const bool byID = false);
    //sort gameobjects by layer ID
    void SortByLayers();
    //Delete all gameobjects, call when scene ends
    void Clear();

    GameObjectManager(const GameObjectManager& other) = delete;
    GameObjectManager& operator = (const GameObjectManager& other) = delete;

private:
    GameObject* FindByName(const std::string& string) const;
    //Find a specific gameobject by tag
    GameObject* FindByTag(const std::string& string) const;
    //Find a specific gameobject by ID
    GameObject* FindByID(const int ID) const;

private:
    std::list<GameObject*> gameObjects_; //list of GameObjects
};

#endif