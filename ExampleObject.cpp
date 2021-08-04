#include "ExampleObject.h"
#include "ID.h"

ExampleObject::ExampleObject(Scene& scene, LP& LP, const sf::Vector2f& position)
{
    scene_ = &scene;
    name_ = "ExampleObject";
    tag_ = "Example";
    position_ = position;
    layerID_ = layer_main;
    ID_ = 0;

    //Sprite set up
    //sprite_ = LP.SetSprite(pic_texture, position_);
}

ExampleObject::~ExampleObject()
{}

void ExampleObject::Update(float delta_time)
{
    //Calculations go here
}

void ExampleObject::Draw(Camera& camera) const
{
    //Draw sprite to layer
    //camera.Draw(sprite_, layer_main);
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