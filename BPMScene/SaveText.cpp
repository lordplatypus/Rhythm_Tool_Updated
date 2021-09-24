#include "SaveText.h"
#include "../Base/ID.h"

SaveText::SaveText(BPMScene& scene, const sf::Vector2f& position, const std::string& BPMFilePath)
{
    scene_ = &scene;
    name_ = "Save";
    tag_ = "Save";
    position_ = position;
    layerID_ = layer_main;
    SetActive(false);

    //Sprite set up
    //sprite_ = scene_->GetLP().SetSprite(Save_texture, position_);
    saveText_ = scene_->GetLP().SetText(main_font, "Saved to: " + BPMFilePath + "BPM", position_, 16);
    scene_->GetLP().SetTextOriginCenter(saveText_);
}

SaveText::~SaveText()
{}

void SaveText::Update(float delta_time)
{
    //Calculations go here
    alpha_ -= delta_time * speed_;
    if (alpha_ <= 0.0f) Kill();
    else saveText_.setFillColor(sf::Color(255, 255, 255, alpha_));
}

void SaveText::Draw(Camera& camera) const
{
    //Draw sprite to layer
    camera.Draw(saveText_, layer_UI);
}