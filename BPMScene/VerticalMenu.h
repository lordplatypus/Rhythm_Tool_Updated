#ifndef VERTICAL_MENU_H_
#define VERTICAL_MENU_H_
#include <SFML/Graphics.hpp>
#include "../Base/Camera.h"

class VerticalMenu
{
public:
    VerticalMenu(sf::Vector2f position, int numOfText, std::vector<sf::Text> textArray, int numToDisplay, int numAboveSelected, int textSpacing, int textPosition = 0);
    ~VerticalMenu();
    void Update(float delta_time);
    void Draw(Camera& camera) const;

    void ScrollUp();
    void ScrollDown();
    void SetDisplay(const bool display);

private:
    VerticalMenu* nextText_{nullptr};
    sf::Vector2f staticPosition_{0.0f, 0.0f};
    sf::Vector2f position_{0.0f, 0.0f};
    sf::Vector2f endPosition_{0.0f, 0.0f};
    sf::Text text_;
    int textPosition_{0};
    int numOfText_{0};
    int menuPosition_{0};
    int alpha_{255};
    int numToDisplay_{0};
    int numAboveSelected_{0};
    int textSpacing_{0};
    bool display_{true};
};

#endif