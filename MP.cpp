#include "MP.h"
#include "ID.h"

//initial

void MP::Load()
{
    LoadMusic();
    LoadSound();
}

void MP::LoadMusic()
{
    // SetMusic(Music Key, "Path to music");
}

void MP::LoadSound()
{
    // SetSound(Sound Key, "Path to sound");
}

//Set && Get

bool MP::SetMusic(const int musicKey, const std::string& filePath)
{
    return musicMap_[musicKey].openFromFile(filePath);
}

const sf::Music& MP::GetMusic(const int musicKey)
{
    return musicMap_[musicKey];
}

bool MP::SetSound(const int soundKey, const std::string& filePath)
{
    if (SetBuffer(soundKey, filePath)) soundMap_[soundKey].setBuffer(bufferMap_[soundKey]);
    else return false;
    return true;
}

bool MP::SetBuffer(const int soundKey, const std::string& filePath)
{
    return bufferMap_[soundKey].loadFromFile(filePath);
}

const sf::Sound& MP::GetSound(const int soundKey)
{
    return soundMap_[soundKey];
}

//Helpful Functions

void MP::PlayMusic(const int musicKey, const bool loop)
{ 
    musicMap_[musicKey].play();
    musicMap_[musicKey].setLoop(loop);
}

void MP::PauseMusic(const int musicKey)
{
    musicMap_[musicKey].pause();
}

void MP::StopMusic(const int musicKey)
{
    musicMap_[musicKey].stop();
}

void MP::LoopMusic(const int musicKey, const bool loop)
{
    musicMap_[musicKey].setLoop(loop);
}

void MP::PlaySound(const int soundKey, const bool loop)
{
    soundMap_[soundKey].play();
    soundMap_[soundKey].setLoop(loop);
}

void MP::PauseSound(const int soundKey)
{
    soundMap_[soundKey].pause();
}

void MP::StopSound(const int soundKey)
{
    soundMap_[soundKey].stop();
}

void MP::LoopSound(const int soundKey, const bool loop)
{
    soundMap_[soundKey].setLoop(loop);
}