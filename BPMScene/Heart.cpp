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
    bigHeart_ = LP_->SetSprite(heart_texture, position_); //frame 1
    smallHeart_ = LP_->SetSprite(small_heart_texture, position_); //frame 2
    //Up the scale
    bigHeart_.setScale(sf::Vector2f(8.0f, 8.0f));
    smallHeart_.setScale(sf::Vector2f(8.0f, 8.0f));

    BPM_ = sf::seconds(1.0f / (120.0f * (1.0f/60.0f))); //set up the default BPM (actually the seconds per beat)
}

Heart::~Heart()
{}

void Heart::Update(float delta_time)
{
    if (autoAnim_)
    {//if autoAnim flag is active, the animation will play in time to the stored BPM and the offset of currently playing song
        lastBeat_ = beat_; //update the last beat, then
        beat_ = MP_->GetMusic(musicID_).getPlayingOffset().asMicroseconds() % BPM_.asMicroseconds(); //update the current beat
        if (lastBeat_ > beat_) 
        {//if the lastbeat is larger then the current beat (signifying the start of the next beat) play an animation
            PlayAnimation();
        }
    }
    
    if (playAnim_) Animation(delta_time); //if the playAnim flag is set, continue updating the animation
}

void Heart::Animation(const float delta_time)
{
    //there are only 2 frames - if big, go small - if small, go big
    if (heartSize_) heartSize_ = false;
    else heartSize_ = true;
    playAnim_ = false; //end playAnim flag
}

void Heart::Draw(Camera& camera) const
{
    //Draw sprite to layer
    if (heartSize_) camera.Draw(bigHeart_, layer_main); //if big, draw big
    else camera.Draw(smallHeart_, layer_main); //if small, draw small
}


void Heart::PlayAnimation()
{
    playAnim_ = true; //set playAnim flag
}


void Heart::SetBPM(const sf::Time& BPM)
{
    BPM_ = BPM;
}

void Heart::SetMusicID(const int musicID)
{
    musicID_ = musicID;
}

void Heart::SetAutoAnimation(const bool autoAnim)
{//sets the autoAnim flag
    autoAnim_ = autoAnim;
}