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
    VerticalMenu* nextText_{nullptr}; //next menu item
    sf::Vector2f staticPosition_{0.0f, 0.0f}; //menu position (doesn't change)
    sf::Vector2f position_{0.0f, 0.0f}; //position of this item (changes)
    sf::Vector2f endPosition_{0.0f, 0.0f}; //end position for this item (for movement calcs)
    sf::Text text_; //actuall text
    int textPosition_{0}; //position in vector (doesn't change)
    int numOfText_{0}; //total menu items
    int menuPosition_{0}; //position within the menu (changes)
    int alpha_{255}; //alpha (changes to signify selection)
    int numToDisplay_{0}; //how many items should be displayed
    int numAboveSelected_{0}; //how many items should be displayed above the selected item
    int textSpacing_{0}; //spacing between menu items
    bool display_{true}; //display flag
};

#endif