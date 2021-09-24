#include "Heart.h"
#include "../Base/ID.h"

Heart::Heart(LP& LP, MP& MP, const sf::Vector2f& position)
{
    LP_ = &LP;
    MP_ = &MP;
    name_ = "Heart";
    tag_ = "Heart";
    position_ = position;
    layerID_ = layer_main;
    SetActive(false);

    //Sprite set up
    bigHeart_ = LP_->SetSprite(heart_texture, position_);
    smallHeart_ = LP_->SetSprite(small_heart_texture, position_);
    bigHeart_.setScale(sf::Vector2f(8.0f, 8.0f));
    smallHeart_.setScale(sf::Vector2f(8.0f, 8.0f));

    BPM_ = sf::seconds(1.0f / (120.0f * (1.0f/60.0f)));
    timeInbetweenFrames_ = sf::seconds(BPM_.asSeconds() / 2.0f);
}

Heart::~Heart()
{}

void Heart::Update(float delta_time)
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

void Heart::Animation(const float delta_time)
{
    // animTimer_ += delta_time;
    // if (animTimer_ > timeInbetweenFrames_.asSeconds()) 
    // {
    //     if (frame_ < 5) frame_++;
    //     else playAnim_ = false;
    //     animTimer_ = 0;
    // }

    if (heartSize_) heartSize_ = false;
    else heartSize_ = true;
    playAnim_ = false;
}

void Heart::Draw(Camera& camera) const
{
    //Draw sprite to layer
    if (heartSize_) camera.Draw(bigHeart_, layer_main);
    else camera.Draw(smallHeart_, layer_main);
}


void Heart::PlayAnimation()
{
    playAnim_ = true;
}


void Heart::SetBPM(const sf::Time& BPM)
{
    BPM_ = BPM;
    timeInbetweenFrames_ = sf::seconds(BPM_.asSeconds() / 10.0f);
}

void Heart::SetMusicID(const int musicID)
{
    musicID_ = musicID;
}

void Heart::SetAutoAnimation(const bool autoAnim)
{
    autoAnim_ = autoAnim;
}