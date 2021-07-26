#include "SceneGame.h"
#include "LP.h"
#include "ID.h"

SceneGame::SceneGame(Game* game) : game_{game}
{}

SceneGame::~SceneGame()
{}

void SceneGame::Init()
{
    //AddGameObject(new Object(position, &pm_, this)); Example
}

void SceneGame::Update(float delta_time)
{
    gom_.Update(delta_time); //update all gameobjects
    gom_.Collision(); //check collision between gameobjects
    gom_.Remove(); //remove "dead" gameobjects
}

void SceneGame::Draw(Camera& camera) const
{
    gom_.Draw(camera); //Regular draw - Draw GameObjects in order based on position in the list
    gom_.DelayedDraw(camera); //draw things after Regular draw is finished, helpful for UI or things that should always be drawn last
}

void SceneGame::AddGameObject(GameObject* gameObject)
{
    gom_.Add(gameObject); //add gameobject to the list of gameobjects
}

GameObject* SceneGame::FindGameObject(const std::string& string, const bool byName, const bool byTag, const bool byID)
{//if byTag and byID are both left to default (false), search by name
    return gom_.Find(string, byName, byTag, byID); //returns a GameObject, returns a nullptr if the GameObject is not found
}

void SceneGame::SortGameObjects()
{
    gom_.SortByLayers();
}

void SceneGame::ChangeScene(const std::string& sceneName)
{
    game_->ChangeScene(sceneName);
}

void SceneGame::End()
{
    gom_.Clear();
}