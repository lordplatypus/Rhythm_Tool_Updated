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
    saveText_ = scene_->GetLP().SetText(main_font, "Saved to: " + BPMFilePath + "BPM", position_, 16); //set up the save text
    scene_->GetLP().SetTextOriginCenter(saveText_); //center the origin
}

SaveText::~SaveText()
{}

void SaveText::Update(float delta_time)
{
    //Calculations go here
    alpha_ -= delta_time * speed_; //alpha goes down at a rate of "speed * delta_time"
    if (alpha_ <= 0.0f) Kill(); //once the alpha goes below 0, remove this object
    else saveText_.setFillColor(sf::Color(255, 255, 255, alpha_)); //update the alpha of the text object
}

void SaveText::Draw(Camera& camera) const
{
    //Draw sprite to layer
    camera.Draw(saveText_, layer_UI);
}