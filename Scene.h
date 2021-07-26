#ifndef SCENE_H_
#define SCENE_H_
#include <string>
#include "GameObject.h"
#include "Camera.h"

class GameObject;

class Scene
{
public:
    virtual ~Scene() = default;
    //This is called everytime this scene is loaded
    virtual void Init() = 0;
    //Scene Update
    virtual void Update(float delta_time) = 0;
    //Scene Draw
    virtual void Draw(Camera& camera) const = 0;
    //Add gameobject to the list of gameobjects
    virtual void AddGameObject(GameObject* gameObject) = 0;
    //Find an object by either ID, Tag, or Name
    virtual GameObject* FindGameObject(const std::string& string, const bool byName = true, const bool byTag = false, const bool byID = false) = 0;
    //Sort the GameObject list based on LayerID (found in GameObjects)
    virtual void SortGameObjects() = 0;
    //Change to a different scene
    virtual void ChangeScene(const std::string& sceneName) = 0;
    //This is called when switching to a different scene, delete unneeded pointers and sprites here
    virtual void End() = 0;
};

#endif