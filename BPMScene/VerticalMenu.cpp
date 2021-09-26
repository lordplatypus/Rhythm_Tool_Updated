#include "VerticalMenu.h"
#include "../Base/Math.h"
#include "../Base/ID.h"

VerticalMenu::VerticalMenu(sf::Vector2f position, int numOfText, std::vector<sf::Text> textArray, int numToDisplay, int numAboveSelected, int textSpacing, int textPosition)
{
    text_ = textArray[textPosition]; //add the text object to the vector
    menuPosition_ = textPosition; //set the initial position within the menu (changes)
    textPosition_ = textPosition + 1; //set the position of the text within the vector (doesn't change)
    numToDisplay_ = numToDisplay; //how many menu items should be displayed
    numAboveSelected_ = numAboveSelected; //how many menu items should be displayed above the selected text
    textSpacing_ = textSpacing; //space between menu items
    staticPosition_ = position; //the overall position of the menu (doesn't change)
    position_ = staticPosition_; //the position of this menu item (changes)
    numOfText_ = numOfText; //how many menu items
    text_.setPosition(position_); //set position of this menu item
    endPosition_ = position_; //set the end position of this menu item (for movement calcs)
    
    if (menuPosition_ != 0) 
    {//if this menu item is not the first item
        alpha_ = 255/4; //lower the alpha, to show that it is not selected
        text_.setFillColor(sf::Color(255, 255, 255, alpha_)); //actually set the alpha
    }

    if (textPosition_ != numOfText_)
    {//if this menu item is not the last item, set up the next menu item
        nextText_ = new VerticalMenu(staticPosition_, numOfText_, textArray, numToDisplay_, numAboveSelected_, textSpacing_, textPosition_);
    }
}

VerticalMenu::~VerticalMenu()
{
    delete nextText_;
}

void VerticalMenu::Update(float delta_time)
{
    if (menuPosition_ >= numToDisplay_) endPosition_.y = staticPosition_.y + (menuPosition_ - numOfText_) * textSpacing_; //position of items that are above the selected item
    else endPosition_.y = staticPosition_.y + menuPosition_ * textSpacing_; //position of items below the selcted item
    if (numOfText_ != textPosition_) nextText_->Update(delta_time); //if not the last item, update the next item

    if (position_ != endPosition_)
    {//if the item hasn't finished its movement
        position_ = Math::Lerp(position_, endPosition_, 10 * delta_time); //gives a more smooth movement
        text_.setPosition(position_); //actually update the position of the item
    }
}

void VerticalMenu::Draw(Camera& camera) const
{
    if (display_ == false) return; //don't draw if the display flag is false

    if (menuPosition_ >= numOfText_ - numAboveSelected_) camera.Draw(text_, layer_UI); //draw above items up to "numAboveSelected_"
    if (menuPosition_ <= numToDisplay_ - 1 - numAboveSelected_) camera.Draw(text_, layer_UI); //draw below items up to "numToDisplay_"

    if (numOfText_ != textPosition_) nextText_->Draw(camera); //if not the last item, draw the next item
}

void VerticalMenu::ScrollUp()
{
    menuPosition_++; //change item position +1
    if (menuPosition_ > numOfText_ - 1) menuPosition_ = 0; //if above the total num of items, cycle back to 0 
    if (menuPosition_ == 0) alpha_ = 255; //if menu position = 0, item is selected
    else alpha_ = 255/4; //else the item is not selected
    text_.setFillColor(sf::Color(255, 255, 255, alpha_)); //actually set alpha
    if (numOfText_ != textPosition_) nextText_->ScrollUp(); //if not the last item, update the next item
}

void VerticalMenu::ScrollDown()
{
    menuPosition_--; //change item position -1
    if (menuPosition_ < 0) menuPosition_ = numOfText_ - 1; //if below 0, cycle to the max num
    if (menuPosition_ == 0) alpha_ = 255; //if menu position = 0, item is selected
    else alpha_ = 255/4; //else the item is not selected
    text_.setFillColor(sf::Color(255, 255, 255, alpha_)); //actually set alpha
    if (numOfText_ != textPosition_) nextText_->ScrollDown(); //if not the last item, update the next item
}

void VerticalMenu::SetDisplay(const bool display)
{
    display_ = display; //set display flag
}