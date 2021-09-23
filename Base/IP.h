#ifndef IP_H_
#define IP_H_
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include "Camera.h"

class IP
{
public:
    IP();
    ~IP();

    //Reset bools used for single button presses
    void Update();

    //Keyboard Stuff

    //Returns true if the button given is currently being pressed - constantly active
    bool GetButton(sf::Keyboard::Key buttonID);
    bool GetButton(sf::Mouse::Button buttonID);
    bool GetButtonDown(sf::Keyboard::Key buttonID);
    bool GetButtonDown(sf::Mouse::Button buttonID);

    //Mouse Stuff

    sf::Vector2f GetMousePosition(Camera& camera);
    void SetMousePosition(sf::Vector2i position);

private:
    std::unordered_map<sf::Keyboard::Key, bool> pressedKeys_;
    std::unordered_map<sf::Mouse::Button, bool> pressedButtons_;
};

#endif