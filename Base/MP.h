#ifndef MP_H_
#define MP_H_
#include <SFML/Audio.hpp>
#include <unordered_map>

class MP
{
public:
    //Initial
    void Load();

private:
    //called by "Load()"
    //set up music and sounds that will be used as soon as the game starts here
    void LoadMusic();
    void LoadSound();

public:
    //Set && Get functions
    //Music
    bool SetMusic(const int musicKey, const std::string& filePath);
    const sf::Music& GetMusic(const int musicKey);
    //Sound Effects
    bool SetSound(const int soundKey, const std::string& filePath);
private:
    bool SetBuffer(const int soundKey, const std::string& filePath);
public:
    const sf::Sound& GetSound(const int soundKey);

    //Helpful functions
    //Music
    void PlayMusic(const int musicKey, const bool loop = false);
    void PauseMusic(const int musicKey);
    void StopMusic(const int musicKey);
    void LoopMusic(const int musicKey, const bool loop);
    //Sound
    void PlaySound(const int key, const bool loop = false);
    void PauseSound(const int key);
    void StopSound(const int key);
    void LoopSound(const int key, const bool loop);

private:
    std::unordered_map<int, sf::Music> musicMap_;
    std::unordered_map<int, sf::SoundBuffer> bufferMap_;
    std::unordered_map<int, sf::Sound> soundMap_;
};

#endif