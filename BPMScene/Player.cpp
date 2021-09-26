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

    //Sprite set up - player sprite (6 frames)
    playerSprites_ = LP_->SetMultiFrameSprite(player_texture, 32, 32, 6, 1, position_);
    for (int i = 0; i < playerSprites_.size(); i++) playerSprites_[i].setScale(sf::Vector2f(6.0f, 6.0f));

    BPM_ = sf::seconds(1.0f / (120.0f * (1.0f/60.0f))); //set up the default BPM (actually the seconds per beat)
    timeInbetweenFrames_ = sf::seconds((1.0f / (120.0f * (1.0f/60.0f))) / 10.0f); //set up the time inbetween animtion frames
}

Player::~Player()
{}

void Player::Update(float delta_time)
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
    playAnim_ = true; //set playAnim flag
    frame_ = 0; //reset the animation frame back to 0
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
{//sets the autoAnim flag
    autoAnim_ = autoAnim;
}