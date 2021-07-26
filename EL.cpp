#include "EL.h"

EL::EL(Camera& camera) : camera_{&camera}
{}

void EL::PollEvent(sf::RenderWindow& render_window)
{
    while (render_window.pollEvent(event_))
    {
        switch (event_.type)
        {
            case sf::Event::Closed:
            isRunning_ = false;
            break;

            case sf::Event::Resized:
            Resized(event_.size);
            break;

            case sf::Event::TextEntered:
            TextEntered(event_.text);
            break;

            case sf::Event::KeyPressed:
            KeyPressed(event_.key);
            break;

            case sf::Event::KeyReleased:
            KeyReleased(event_.key);
            break;

            default:
            break;
        }
    }
}

bool EL::IsRunning()
{
    return isRunning_;
}

void EL::Resized(const sf::Event::SizeEvent& sizeEvent)
{
    resized_ = sf::Vector2u(sizeEvent.width, sizeEvent.height);
    ResizeViews(resized_); //commet this line out if auto scaling the views when the window is resized is not desired
}

void EL::ResizeViews(const sf::Vector2u& sizeEvent)
{
    sf::FloatRect viewport(0.0f, 0.0f, 1.0f, 1.0f);

    float screenwidth = sizeEvent.x / camera_->GetAspectRatio().x;
    float screenheight = sizeEvent.y / camera_->GetAspectRatio().y;

    if(screenwidth > screenheight)
    {
        viewport.width = screenheight / screenwidth;
        viewport.left = (1.0f - viewport.width) / 2.0f;
    }
    else if(screenwidth < screenheight)
    {
        viewport.height = screenwidth / screenheight;
        viewport.top = (1.0f - viewport.height) / 2.0f;
    }

    for (auto i : camera_->GetVectorViewNames())
    {
        camera_->SetViewport(i, viewport);
    }
}

void EL::TextEntered(const sf::Event::TextEvent& textEvent)
{
    if (!GetTextEnteredActive()) return;
    switch (textEvent.unicode)
    {
        case '\r':
        break;

        case '\b':
        Backspace();
        break;
    
        default:
        textEntered_ += textEvent.unicode;
        break;
    }
}

void EL::Backspace()
{
    textEntered_.erase(textEntered_.getSize() - 1);
}

void EL::KeyPressed(const sf::Event::KeyEvent& keyEvent)
{//For now this is empty as I use another way to get input

}

void EL::KeyReleased(const sf::Event::KeyEvent& keyEvent)
{//This is just to exit the game
    if (keyEvent.code == sf::Keyboard::Escape) isRunning_ = false;
}


//Get && Set functions

const sf::Vector2u& EL::GetResized() const
{
    return resized_;
}

void EL::SetTextEntered(const sf::String& text)
{
    textEntered_ = text;
}

const sf::String& EL::GetTextEntered() const
{
    return textEntered_;
}

void EL::SetTextEnteredActive(bool active)
{
    textEnteredActive_ = active;
}

bool EL::GetTextEnteredActive()
{
    return textEnteredActive_;
}