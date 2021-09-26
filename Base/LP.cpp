#include "LP.h"
#include "ID.h"

//initial

void LP::Load()
{
    LoadTexture();
    LoadFont();
}

void LP::LoadTexture()
{
    // SetTexture(Texture Key, "Path to texture", Optional: size of texture);
    SetTexture(background_texture, "./Resources/Background.png");
    SetTexture(player_texture, "./Resources/Player_Roboko.png");
    SetTexture(heart_texture, "./Resources/Heart.png");
    SetTexture(small_heart_texture, "./Resources/HeartSmall.png");
}

void LP::LoadFont()
{
    // SetFont(Font Key, "Path to Font");
    SetFont(main_font, "./Resources/Blue Sky 8x8.ttf");
}


//Set && Get

bool LP::SetTexture(const int textureKey, const std::string& filePath)
{
    return textureMap_[textureKey].loadFromFile(filePath);
}

bool LP::SetTexture(const int textureKey, const std::string& filePath, int width, int height)
{
    return textureMap_[textureKey].loadFromFile(filePath, sf::IntRect(0, 0, width, height));
}

bool LP::SetTexture(const int textureKey, const std::string& filePath, const sf::Vector2i& size)
{
    return textureMap_[textureKey].loadFromFile(filePath, sf::IntRect(0, 0, size.x, size.y));
}

bool LP::SetTexture(const int textureKey, const std::string& filePath, const sf::IntRect& size)
{
    return textureMap_[textureKey].loadFromFile(filePath, size);
}

const sf::Texture& LP::GetTexture(const int textureKey)
{
    return textureMap_[textureKey];
}

void LP::SetFont(const int fontKey, const std::string& filePath)
{
    fontMap_[fontKey].loadFromFile(filePath);
}

const sf::Font& LP::GetFont(const int fontKey)
{
    return fontMap_[fontKey];
}


//Helpful functions - I think

sf::Sprite LP::SetSprite(const int textureKey, const sf::Vector2f& position)
{
    sf::Sprite temp;
    temp.setTexture(textureMap_[textureKey]);
    temp.setPosition(position);
    return temp;
}

sf::Sprite LP::SetSprite(const int textureKey, const int cellWidth, const int cellHeight, const int cellID, const sf::Vector2f& position)
{
    sf::Sprite temp;
    temp.setTexture(textureMap_[textureKey]);
    sf::Vector2u textureSize = temp.getTexture()->getSize();
    temp.setTextureRect(sf::IntRect(cellID % (textureSize.x / cellWidth) * cellWidth, cellID / (textureSize.x / cellWidth) * cellHeight, cellWidth, cellHeight));
    temp.setPosition(position);
    return temp;
}

std::vector<sf::Sprite> LP::SetMultiFrameSprite(const int textureKey, const int cellWidth, const int cellHeight, const int numOfColumns, const int numOfRows, const sf::Vector2f& position)
{
    std::vector<sf::Sprite> spriteArray;
    for (int i = 0; i < numOfRows; i++)
    {
        for (int j = 0; j < numOfColumns; j++)
        {
            sf::Sprite temp;
            temp.setTexture(textureMap_[textureKey]);
            temp.setTextureRect(sf::IntRect(cellWidth * j, cellHeight * i, cellWidth, cellHeight));
            temp.setPosition(position);
            spriteArray.push_back(temp);
        }
    }
    return spriteArray;
}

void LP::SetSpriteHorizontalFlip(sf::Sprite& sprite, const bool flip)
{
    if (flip && sprite.getScale().x > 0)
    {
        sprite.scale(-1.0f, 1.0f);
        sprite.setOrigin(sprite.getLocalBounds().width, sprite.getOrigin().y);
    }
    else if (!flip && sprite.getScale().x < 0)
    {
        sprite.scale(-1.0f, 1.0f);
        sprite.setOrigin(0, sprite.getOrigin().y);
    }
}

void LP::SetSpriteOriginCenter(sf::Sprite& sprite)
{
    sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
}

sf::Text LP::SetText(const int fontKey, const std::string& string, const sf::Vector2f& position, const int textSize, const sf::Vector2f& scale)
{
    sf::Text text;
    text.setFont(fontMap_[fontKey]);
    text.setCharacterSize(textSize);
    text.setPosition(position);
    text.setFillColor(sf::Color::White);
    text.setString(string);
    text.setScale(scale);
    return text;
}

void LP::SetTextOriginCenter(sf::Text& text)
{
    text.setOrigin(text.getLocalBounds().width / 2, text.getLocalBounds().height / 2);
}

TileMap LP::SetTileMap(const int textureKey, sf::Vector2u tileSize, const std::vector<std::vector<int>> map, sf::Vector2f position, int width, int height)
{
    TileMap temp;
    temp.Load(textureMap_[textureKey], tileSize, map, position, width, height);
    return temp;
}