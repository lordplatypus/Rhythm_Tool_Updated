#include "Camera.h"

//Camera::Camera(sf::RenderWindow* render_window) : window_{render_window} {}
Camera::Camera(sf::RenderWindow* renderWindow, const sf::Vector2f& aspectRatio)
{
    renderWindow_ = renderWindow;
    SetAspectRatio(aspectRatio);
    SetView("Main");
    SetCurrentView("Main");
}

Camera::~Camera() 
{}

const sf::RenderWindow& Camera::GetRenderWindow() const
{
    return *renderWindow_;
}

void Camera::SetAspectRatio(const sf::Vector2f& aspectRatio)
{
    aspectRatio_ = aspectRatio;
}

const sf::Vector2f& Camera::GetAspectRatio() const
{
    return aspectRatio_;
}

void Camera::SetView(const std::string& viewName)
{
    views_[viewName] = sf::View(sf::FloatRect(0.0f, 0.0f, aspectRatio_.x, aspectRatio_.y));
}

void Camera::SetView(const std::string& viewName, float width, float height)
{
    views_[viewName] = sf::View(sf::FloatRect(0.0f, 0.0f, width, height));
}

void Camera::SetView(const std::string& viewName, const sf::Vector2f& size)
{
    views_[viewName] = sf::View(sf::FloatRect(0.0f, 0.0f, size.x, size.y));
}

void Camera::SetView(const std::string& viewName, const sf::FloatRect& viewArea)
{
    views_[viewName] = sf::View(viewArea);
}

const sf::View& Camera::GetView(const std::string& viewName)
{
    return views_[viewName];
}

void Camera::SetViewport(const std::string& viewName, const sf::FloatRect& viewport)
{
    views_[viewName].setViewport(viewport);
}

void Camera::SetViewport(const std::string& viewName, const sf::Vector2f& viewSize)
{
    views_[viewName].setSize(viewSize);
}

void Camera::SetViewCenter(const std::string& viewName, const sf::Vector2f& center)
{
    views_[viewName].setCenter(center);
}

void Camera::SetCurrentView(const std::string& viewName)
{
    renderWindow_->setView(views_[viewName]);
    currentView_ = viewName;
}

const std::string& Camera::GetCurrentViewName() const
{
    return currentView_;
}


std::vector<std::string> Camera::GetVectorViewNames() const
{
    std::vector<std::string> names;
    for (auto i : views_)
    {
        names.push_back(i.first);
    }
    return names;
}


void Camera::Draw(sf::CircleShape objectToDraw)
{
    renderWindow_->draw(objectToDraw);
}

void Camera::Draw(sf::RectangleShape objectToDraw)
{
    renderWindow_->draw(objectToDraw);
}

void Camera::Draw(sf::Sprite objectToDraw)
{
    renderWindow_->draw(objectToDraw);
}

void Camera::Draw(sf::Text objectToDraw)
{
    renderWindow_->draw(objectToDraw);
}

void Camera::Draw(TileMap objectToDraw)
{
    renderWindow_->draw(objectToDraw);
}