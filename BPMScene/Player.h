#ifndef PLAYER_H_
#define PLAYER_H_
#include "../Base/GameObject.h"
#include "../Base/LP.h"
#include "../Base/MP.h"

class Player : public GameObject
{
public:
    Player(LP& LP, MP& MP, const sf::Vector2f& position);
    ~Player() override;
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
    std::vector<sf::Sprite> playerSprites_;

    //Animation
    float animTimer_{0.0f};
    int frame_{0};
    bool playAnim_{false};
    sf::Time BPM_;
    sf::Time timeInbetweenFrames_;
    int beat_{0};
    int lastBeat_{0};
    int musicID_{0};
    bool autoAnim_{false};
};

#endif