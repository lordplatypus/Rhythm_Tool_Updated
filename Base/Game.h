#ifndef GAME_H_
#define GAME_H_
#include <unordered_map>
#include "Scene.h"
#include "LP.h"
#include "MP.h"
#include "Camera.h"

class Game
{
public:
    Game();
    ~Game();
    //Update Game
    void Update(float delta_time);
    //Draw Game
    void Draw(Camera& camera);
    //Add a Scene to the scene map
    void AddScene(const std::string& name, Scene* scene);
    //Switch to a different scene
    void ChangeScene(const std::string& newScene);
    //End a scene
    void EndScene();

    LP& GetLP();
    MP& GetMP();

    //Called on program shutdown, delete scenes here
    void Clear();

    Game(const Game& other) = delete;
    Game& operator = (const Game& other) = delete;

private:
    //Stores scenes with string key
    std::unordered_map<std::string, Scene*> scenes_;
    //Current loaded scene
    Scene* scene_ {nullptr};
    //Load Assets
    LP LP_;
    MP MP_;
};

#endif