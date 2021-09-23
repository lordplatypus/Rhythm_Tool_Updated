#ifndef EL_H_
#define EL_H_
#include <SFML/Graphics.hpp>
#include "Camera.h"

class EL //Event Listener
{
public:
    EL(Camera& camera);
    void PollEvent(sf::RenderWindow& render_window);
    bool IsRunning();

private:
    //Resized Event
    void Resized(const sf::Event::SizeEvent& sizeEvent);
    void ResizeViews(const sf::Vector2u& sizeEvent);
    //Text Entered Event
    void TextEntered(const sf::Event::TextEvent& textEvent);
    void Backspace();

private:
    //Key Press && Release Event
    void KeyPressed(const sf::Event::KeyEvent& keyEvent);
    void KeyReleased(const sf::Event::KeyEvent& keyEvent);

public:
    //Get && Set Functions
    const sf::Vector2u& GetResized() const;
    void SetTextEntered(const sf::String& text);
    const sf::String& GetTextEntered() const;
    void SetTextEnteredActive(bool active);
    bool GetTextEnteredActive();

private:
    Camera* camera_{nullptr};
    sf::Event event_; //Events
    bool isRunning_{true}; //For the main Game Loop
    sf::Vector2u resized_{0, 0}; //store resize event
    sf::String textEntered_{""}; //to store text entered, different from key press
    bool textEnteredActive_{false}; //allow text to be stored in textEntered
};

#endif