#include "Background.h"
#include "../Base/ID.h"

Background::Background(BPMScene& scene, const sf::Vector2f& position)
{
    scene_ = &scene;
    name_ = "Background";
    tag_ = "Background";
    position_ = position;
    layerID_ = layer_main;
    SetActive(false);

    //Sprite set up
    sprite_ = scene_->GetLP().SetSprite(background_texture, position_);
}

Background::~Background()
{}

void Background::Update(float delta_time)
{
    //Calculations go here
}

void Background::Draw(Camera& camera) const
{
    //Draw sprite to layer
    camera.Draw(sprite_, layer_main);
}