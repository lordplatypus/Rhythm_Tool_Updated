#include "ExampleObject.h"
#include "ID.h"
#include "LP.h"
#include "IP.h"

ExampleObject::ExampleObject(Scene* scene, const sf::Vector2f& position)
{
    scene_ = scene;
    name_ = "ExampleObject";
    tag_ = "Example";
    position_ = position;
    layerID_ = layer_main_;
    ID_ = 0;

    //Sprite set up
    //sprite_ = LP::SetSprite("texture id", position_);
}

ExampleObject::~ExampleObject()
{}

void ExampleObject::Update(float delta_time)
{
    //Calculations go here
}

void ExampleObject::Draw(Camera& camera) const
{
    //Set view (if using multiple views)
    //render_window.setView(*scene_->FindView("Name Of View"));

    //Draw sprite to render window
    //render_window.draw(sprite_);
}

void ExampleObject::DelayedDraw(Camera& camera) const
{
    //same as Draw
    //this function will be called after Draw
    //Good for things that need to be drawn last - UI
}

void ExampleObject::ReactOnCollision(GameObject& other)
{
    //If Object B collided with this Object (A), then B's info is sent to A

    if (other.GetName() == "Player")
    {
        //EX: if the collided object is "player" then do this
    }
}