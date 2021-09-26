#ifndef HEART_H_
#define HEART_H_
#include "../Base/GameObject.h"
#include "../Base/LP.h"
#include "../Base/MP.h"

class Heart : public GameObject
{
public:
    Heart(LP& LP, MP& MP, const sf::Vector2f& position);
    ~Heart() override;
    void Update(float delta_time) override;
    void Animation(const float delta_time);
    void Draw(Camera& camera) const override;

    void PlayAnimation();

    void SetBPM(const sf::Time& BPM);
    void SetMusicID(const int musicID);
    void SetAutoAnimation(const bool autoAnim);

private:
    LP* LP_{nullptr}; //visual stuff
    MP* MP_{nullptr}; //audio stuff
    sf::Sprite bigHeart_; //big heart sprite
    sf::Sprite smallHeart_; //small heart sprite

    //Animation
    bool heartSize_{false}; //true = big, false = small
    bool playAnim_{false}; //play animation flag
    sf::Time BPM_; //beats per minute (actually stores seconds per beat)
    int beat_{0}; //Stores the time of the current beat (resets to 0 at the start of the next beat)
    int lastBeat_{0}; //Stores beat_ when beat_ is updated (for auto animation calcs)
    int musicID_{0}; //current playing music ID 
    bool autoAnim_{false}; //auto animation flag
};

#endif