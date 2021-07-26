#include "IP.h"

IP::IP()
{}

IP::~IP()
{}

void IP::Update()
{
    for (auto key : pressedKeys_)
    {
        if (!sf::Keyboard::isKeyPressed(key.first)) pressedKeys_[key.first] = false;
    }
    for (auto button : pressedButtons_)
    {
        if (!sf::Mouse::isButtonPressed(button.first)) pressedButtons_[button.first] = false;
    }
}

bool IP::GetButton(sf::Keyboard::Key buttonID)
{
    return sf::Keyboard::isKeyPressed(buttonID);
}

bool IP::GetButton(sf::Mouse::Button buttonID)
{
    return sf::Mouse::isButtonPressed(buttonID);
}

bool IP::GetButtonDown(sf::Keyboard::Key buttonID)
{
    if (!sf::Keyboard::isKeyPressed(buttonID) || pressedKeys_[buttonID]) return false;
    pressedKeys_[buttonID] = true;
    return true;
}

bool IP::GetButtonDown(sf::Mouse::Button buttonID)
{
    if (!sf::Mouse::isButtonPressed(buttonID) || pressedButtons_[buttonID]) return false;
    pressedButtons_[buttonID] = true;
    return true;
}

//Mouse

sf::Vector2f IP::GetMousePosition(Camera& camera)
{
    //Get mouse position (pixel coordinates)
    sf::Vector2i mousePosition = sf::Mouse::getPosition(camera.GetRenderWindow());
    //return mouse position after converting it to world coordinates
    return camera.GetRenderWindow().mapPixelToCoords(mousePosition);
}

void IP::SetMousePosition(sf::Vector2i position)
{
    sf::Mouse::setPosition(position);
}