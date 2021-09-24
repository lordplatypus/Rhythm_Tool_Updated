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
    LP* LP_{nullptr};
    MP* MP_{nullptr};
    sf::Sprite bigHeart_;
    sf::Sprite smallHeart_;

    //Animation
    bool heartSize_{false};
    bool playAnim_{false};
    sf::Time BPM_;
    sf::Time timeInbetweenFrames_;
    int beat_{0};
    int lastBeat_{0};
    int musicID_{0};
    bool autoAnim_{false};
};

#endif