#ifndef BPM_SCENE_H_
#define BPM_SCENE_H_
#include "../Base/Scene.h"
#include "../Base/Game.h"
#include "../Base/GameObjectManager.h"
#include "../Base/IP.h"
#include "FileManager.h"
#include "VerticalMenu.h"
#include "Player.h"
#include "Heart.h"

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

public:
    LP& GetLP();
    MP& GetMP();

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
    sf::Text displayMusicDirectory;
    sf::Text displayBPMSaveDirectory;

    //Music Select
    int musicID = 0;
    int selectedMusicID = 0;

    //Numbers
    std::vector<int> listOfBeats;
    int beatsPerMin{0};
    float secPerBeat{0};
    int beatTimer{0}; //INT
    int zeroOutTime{0};
    int count{0};

    std::unordered_map<std::string, sf::Time> secPerBeatMap_;

    bool firstTime = true;
    bool startOfBeat = false;

    //Objects
    Player* player_;
    Heart* heart_;
};

#endif