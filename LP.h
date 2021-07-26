#ifndef LP_H_
#define LP_H_
#include <SFML/Graphics.hpp>
#include <vector>
#include <unordered_map>
#include "TileMap.h"

class LP
{
public:
    //Initial
    void Load();

private:
    //called by "Load()"
    //set up textures and fonts that will be used as soon as the game starts here
    void LoadTexture();
    void LoadFont();

public:
    //Set && Get functions
    //Textures
    bool SetTexture(const int textureKey, const std::string& filePath);
    bool SetTexture(const int textureKey, const std::string& filePath, int width, int height);
    bool SetTexture(const int textureKey, const std::string& filePath, const sf::Vector2i& size);
    bool SetTexture(const int textureKey, const std::string& filePath, const sf::IntRect& size);
    const sf::Texture& GetTexture(const int textureKey);    
    //Text
    void SetFont(const int fontKey, const std::string& filePath);
    const sf::Font& GetFont(const int fontKey);

    //Helpful Functions
    //Sprites
    sf::Sprite SetSprite(const int textureKey, const sf::Vector2f& position = sf::Vector2f(0.0f, 0.0f));
    sf::Sprite SetSprite(const int textureKey, const int cellWidth, const int cellHeight, const int cellID, const sf::Vector2f& position = sf::Vector2f(0.0f, 0.0f));
    std::vector<sf::Sprite> SetMultiFrameSprite(const int textureKey, const int cellWidth, const int cellHeight, const int numOfColumns, const int numOfRows, const sf::Vector2f& position = sf::Vector2f(0.0f, 0.0f));
    void SetSpriteHorizontalFlip(sf::Sprite& sprite, const bool flip);
    void SetSpriteOriginCenter(sf::Sprite& sprite);
    //Text
    sf::Text SetText(const int fontKey, const std::string& string, const sf::Vector2f& position = sf::Vector2f(0.0f, 0.0f), const int textSize = 32, const sf::Vector2f& scale = sf::Vector2f(1.0f, 1.0f));
    void SetTextOriginCenter(sf::Text& text);
    //TileMap
    TileMap SetTileMap(const int textureKey, sf::Vector2u tileSize, const std::vector<std::vector<int>> map, sf::Vector2f position, int width, int height);

private:
    std::unordered_map<int, sf::Texture> textureMap_;
    std::unordered_map<int, sf::Font> fontMap_;
};

#endif