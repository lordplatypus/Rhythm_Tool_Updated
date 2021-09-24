#include "Player.h"
#include "../Base/ID.h"

Player::Player(LP& LP, MP& MP, const sf::Vector2f& position)
{
    LP_ = &LP;
    MP_ = &MP;
    name_ = "Player";
    tag_ = "Player";
    position_ = position;
    layerID_ = layer_main;
    SetActive(false);

    //Sprite set up
    playerSprites_ = LP_->SetMultiFrameSprite(player_texture, 32, 32, 6, 1, position_);
    for (int i = 0; i < playerSprites_.size(); i++) playerSprites_[i].setScale(sf::Vector2f(6.0f, 6.0f));

    BPM_ = sf::seconds(1.0f / (120.0f * (1.0f/60.0f)));
    timeInbetweenFrames_ = sf::seconds((1.0f / (120.0f * (1.0f/60.0f))) / 10.0f);
}

Player::~Player()
{}

void Player::Update(float delta_time)
{
    if (autoAnim_)
    {
        lastBeat_ = beat_;
        beat_ = MP_->GetMusic(musicID_).getPlayingOffset().asMicroseconds() % BPM_.asMicroseconds();
        if (lastBeat_ > beat_) 
        {
            PlayAnimation();
        }
    }
    
    if (playAnim_) Animation(delta_time);
}

void Player::Animation(const float delta_time)
{
    animTimer_ += delta_time;
    if (animTimer_ > timeInbetweenFrames_.asSeconds()) 
    {
        if (frame_ < 5) frame_++;
        else playAnim_ = false;
        animTimer_ = 0;
    }
}

void Player::Draw(Camera& camera) const
{
    //Draw sprite to layer
    camera.Draw(playerSprites_[frame_], layer_main);
}


void Player::PlayAnimation()
{
    playAnim_ = true;
    frame_ = 0;
}


void Player::SetBPM(const sf::Time& BPM)
{
    BPM_ = BPM;
}

void Player::SetMusicID(const int musicID)
{
    musicID_ = musicID;
}

void Player::SetAutoAnimation(const bool autoAnim)
{
    autoAnim_ = autoAnim;
}