#ifndef CAMERA_H_
#define CAMERA_H_
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <map>
#include "Layer.h"

class Camera
{
public:
    Camera() = default;
    Camera(sf::RenderWindow* renderWindow, const sf::Vector2f& aspectRatio);
    ~Camera();

    //Draw drawable objects - Default to layer 0
    void Draw(const sf::Drawable& objectToDraw, const int layerID = 0);

    //Get the render window
    const sf::RenderWindow& GetRenderWindow() const;
    //Set the game aspect ratio
    void SetAspectRatio(const sf::Vector2f& aspectRatio);
    //Get the game aspect ratio
    const sf::Vector2f& GetAspectRatio() const;
    //create a new view with default size
    void AddView(const int viewID);
    //Create a new view
    void AddView(const int viewID, float width, float height);
    //Create a new view
    void AddView(const int viewID, const sf::Vector2f& size);
    //Create a new view
    void AddView(const int viewID, const sf::FloatRect& viewArea);
    //returns a view
    const sf::View& GetView(const int viewID);

    void SetViewport(const int viewID, const sf::FloatRect& viewport);
    void SetViewport(const int viewID, const sf::Vector2f& viewport);
    void SetViewCenter(const int viewID, const sf::Vector2f& center);

    void SetCurrentView(const int viewID);
    const int GetCurrentViewID() const;

    std::vector<int> GetVectorViewIDs() const;

    //Add a layer
    void AddLayer(const int layerID);
    //Draw layers once all drawable objects are accumulated - called in main
    void DrawLayers();
    //Clear the layers so they are ready for the next frame - called in main
    void ClearLayers();


    Camera(const Camera& other) = delete;
    Camera& operator = (const Camera& other) = delete;

private:
    sf::RenderWindow* renderWindow_;
    std::map<int, Layer*> layers_;
    std::unordered_map<int, sf::View> views_;
    sf::Vector2f aspectRatio_;
    int currentView_{0};
};

#endif