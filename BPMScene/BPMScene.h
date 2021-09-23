#ifndef BPM_SCENE_H_
#define BPM_SCENE_H_
#include "../Base/Scene.h"
#include "../Base/Game.h"
#include "../Base/GameObjectManager.h"
#include "../Base/IP.h"
#include "FileManager.h"
#include "VerticalMenu.h"

class BPMScene : public Scene
{
public:
    BPMScene(Game* game);
    ~BPMScene();
    virtual void Init() override;
    virtual void Update(float delta_time) override;
    virtual void Draw(Camera& camera) const override;
    virtual void AddGameObject(GameObject* gameObject) override;
    virtual GameObject* FindGameObject(const std::string& string, const bool byName = true, const bool byTag = false, const bool byID = false) override;
    virtual void ChangeScene(const std::string& sceneName) override;
    virtual void End() override;

private:
    void ImportSongs();
    void MainMenu();
    void MusicSelectMenu();
    void BPMSetUp();
    void MusicPlayBack();
    void SaveBPMForSelectedSong();

private:
    Game* game_{nullptr};
    GameObjectManager gom_;
    IP IP_;
    FileManager FM_;

    //enum for states
    enum State {Menu, MusicSelect, SetUp, PlayBack, Save};
    State state = Menu;

    //Menu Text
    std::vector<sf::Text> menuText_;
    std::vector<sf::Text> musicTitles_;
    int selectedOption = 0;
    VerticalMenu* menu_{nullptr};
    VerticalMenu* musicMenu_{nullptr};
    sf::Text instructions;
    sf::Text savedText;
    sf::Text displayMusicTitle;
    sf::Text displayBeatsPerMin;
    sf::Text displaySecPerBeat;
    sf::Text displayBeatTimer;
    sf::Text displayBeatCount;

    //Music Select
    int musicID = 0;
    int selectedMusicID = 0;

    //Numbers
    std::vector<float> listOfBeats;
    float beatsPerMin{0};
    float secPerBeat{0};
    float beatTimer{0};
    float zeroOutTime{0};
    int count{0};

    std::unordered_map<std::string, sf::Time> secPerBeatMap_;

    bool firstTime = true;
};

#endif