#include "Camera.h"
#include "ID.h"

//Camera::Camera(sf::RenderWindow* render_window) : window_{render_window} {}
Camera::Camera(sf::RenderWindow* renderWindow, const sf::Vector2f& aspectRatio)
{
    renderWindow_ = renderWindow;
    SetAspectRatio(aspectRatio);
}

Camera::~Camera() 
{}


void Camera::Draw(const sf::Drawable& objectToDraw, const int layerID)
{
    layers_[layerID]->Draw(objectToDraw);
}


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

void Camera::AddView(const int viewID)
{
    views_[viewID] = sf::View(sf::FloatRect(0.0f, 0.0f, aspectRatio_.x, aspectRatio_.y));
}

void Camera::AddView(const int viewID, float width, float height)
{
    views_[viewID] = sf::View(sf::FloatRect(0.0f, 0.0f, width, height));
}

void Camera::AddView(const int viewID, const sf::Vector2f& size)
{
    views_[viewID] = sf::View(sf::FloatRect(0.0f, 0.0f, size.x, size.y));
}

void Camera::AddView(const int viewID, const sf::FloatRect& viewArea)
{
    views_[viewID] = sf::View(viewArea);
}

const sf::View& Camera::GetView(const int viewID)
{
    return views_[viewID];
}

void Camera::SetViewport(const int viewID, const sf::FloatRect& viewport)
{
    views_[viewID].setViewport(viewport);
}

void Camera::SetViewport(const int viewID, const sf::Vector2f& viewSize)
{
    views_[viewID].setSize(viewSize);
}

void Camera::SetViewCenter(const int viewID, const sf::Vector2f& center)
{
    views_[viewID].setCenter(center);
}

void Camera::SetCurrentView(const int viewID)
{
    renderWindow_->setView(views_[viewID]);
    currentView_ = viewID;
}

const int Camera::GetCurrentViewID() const
{
    return currentView_;
}


std::vector<int> Camera::GetVectorViewIDs() const
{
    std::vector<int> IDs;
    for (auto i : views_)
    {
        IDs.push_back(i.first);
    }
    return IDs;
}


void Camera::AddLayer(const int layerID)
{
    layers_[layerID] = new Layer;
}

void Camera::DrawLayers()
{
    for (auto layer : layers_) 
    {
        if (layer.first == layer_UI) SetCurrentView(view_UI);
        else SetCurrentView(view_main);
        renderWindow_->draw(*layer.second);
    }
}

void Camera::ClearLayers()
{
    for (auto layer : layers_) layer.second->Clear();
}