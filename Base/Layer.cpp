#include "Layer.h"

// void Layer::AddToLayer(sf::Drawable* objectToDraw)
// {
//     drawables_.push_back(objectToDraw);
// }

// void Layer::RemoveFromLayer(sf::Drawable* objectToDraw)
// {
//     for (auto i = drawables_.begin(); i != drawables_.end(); i++)
//     {
//         if (*i == objectToDraw) drawables_.erase(i);
//     }
// }

void Layer::Draw(const sf::Drawable& objectToDraw)
{
    drawables_.push_back(&objectToDraw);
}

void Layer::Clear()
{
    drawables_.clear();
}

void Layer::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (auto drawable : drawables_) target.draw(*drawable);
}