#ifndef CAMERA_H_
#define CAMERA_H_
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include "TileMap.h"

class Camera
{
public:
    Camera() = default;
    Camera(sf::RenderWindow* renderWindow, const sf::Vector2f& aspectRatio);
    ~Camera();

    //Get the render window
    const sf::RenderWindow& GetRenderWindow() const;
    //Set the game aspect ratio
    void SetAspectRatio(const sf::Vector2f& aspectRatio);
    //Get the game aspect ratio
    const sf::Vector2f& GetAspectRatio() const;
    //create a new view with default size
    void SetView(const std::string& viewName);
    //Create a new view
    void SetView(const std::string& viewName, float width, float height);
    //Create a new view
    void SetView(const std::string& viewName, const sf::Vector2f& size);
    //Create a new view
    void SetView(const std::string& viewName, const sf::FloatRect& viewArea);
    //returns a view
    const sf::View& GetView(const std::string& viewName);

    void SetViewport(const std::string& viewName, const sf::FloatRect& viewport);
    void SetViewport(const std::string& viewName, const sf::Vector2f& viewport);
    void SetViewCenter(const std::string& viewName, const sf::Vector2f& center);

    void SetCurrentView(const std::string& viewName);
    const std::string& GetCurrentViewName() const;

    std::vector<std::string> GetVectorViewNames() const;

    void Draw(sf::CircleShape objectToDraw);
    void Draw(sf::RectangleShape objectToDraw);
    void Draw(sf::Sprite objectToDraw);
    void Draw(sf::Text objectToDraw);
    void Draw(TileMap objectToDraw);

    Camera(const Camera& other) = delete;
    Camera& operator = (const Camera& other) = delete;

private:
    sf::RenderWindow* renderWindow_;
    std::unordered_map<std::string, sf::View> views_;
    sf::Vector2f aspectRatio_;
    std::string currentView_{"Main"};
};

#endif