#ifndef LAYER_H_
#define LAYER_H_
#include <SFML/Graphics.hpp>
#include "TileMap.h"

class Layer : public sf::Drawable, public sf::Transformable
{
public:
    //void AddToLayer(sf::Drawable* objectToDraw);
    //void RemoveFromLayer(sf::Drawable* objectToDraw);
    void Draw(const sf::Drawable& objectToDraw);
    void Clear();

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
    std::vector<const sf::Drawable*> drawables_;
};

#endif