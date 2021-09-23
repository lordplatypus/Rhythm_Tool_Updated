#include "VerticalMenu.h"
#include "../Base/Math.h"
#include "../Base/ID.h"

VerticalMenu::VerticalMenu(sf::Vector2f position, int numOfText, std::vector<sf::Text> textArray, int numToDisplay, int numAboveSelected, int textSpacing, int textPosition)
{
    text_ = textArray[textPosition];
    menuPosition_ = textPosition;
    textPosition_ = textPosition + 1;
    numToDisplay_ = numToDisplay;
    numAboveSelected_ = numAboveSelected;
    textSpacing_ = textSpacing;
    staticPosition_ = position;
    position_ = staticPosition_;
    if (menuPosition_ == numOfText_ - 1) position_.y = staticPosition_.y - 64;
    else position_.y = staticPosition_.y + menuPosition_ * 64;
    text_.setPosition(position_);
    endPosition_ = position_;
    numOfText_ = numOfText;
    if (menuPosition_ != 0) 
    {
        alpha_ = 255/4;
        text_.setFillColor(sf::Color(255, 255, 255, alpha_));
    }

    if (textPosition_ != numOfText_)
    {
        nextText_ = new VerticalMenu(staticPosition_, numOfText_, textArray, numToDisplay_, numAboveSelected_, textSpacing_, textPosition_);
    }
}

VerticalMenu::~VerticalMenu()
{
    delete nextText_;
}

void VerticalMenu::Update(float delta_time)
{
    if (menuPosition_ >= numToDisplay_) endPosition_.y = staticPosition_.y + (menuPosition_ - numOfText_) * textSpacing_;
    else endPosition_.y = staticPosition_.y + menuPosition_ * textSpacing_;
    if (numOfText_ != textPosition_) nextText_->Update(delta_time);

    if (position_ != endPosition_)
    {
        position_ = Math::Lerp(position_, endPosition_, 10 * delta_time);
        text_.setPosition(position_);
    }
}

void VerticalMenu::Draw(Camera& camera) const
{
    if (display_ == false) return;

    if (menuPosition_ >= numOfText_ - numAboveSelected_) camera.Draw(text_, layer_UI);
    if (menuPosition_ <= numToDisplay_ - 1 - numAboveSelected_) camera.Draw(text_, layer_UI);

    if (numOfText_ != textPosition_) nextText_->Draw(camera);
}

void VerticalMenu::ScrollUp()
{
    menuPosition_++;
    if (menuPosition_ > numOfText_ - 1) menuPosition_ = 0; 
    if (menuPosition_ == 0) alpha_ = 255;
    else alpha_ = 255/4;
    text_.setFillColor(sf::Color(255, 255, 255, alpha_));
    if (numOfText_ != textPosition_) nextText_->ScrollUp();
}

void VerticalMenu::ScrollDown()
{
    menuPosition_--;
    if (menuPosition_ < 0) menuPosition_ = numOfText_ - 1;
    if (menuPosition_ == 0) alpha_ = 255;
    else alpha_ = 255/4;
    text_.setFillColor(sf::Color(255, 255, 255, alpha_));
    if (numOfText_ != textPosition_) nextText_->ScrollDown();
}

void VerticalMenu::SetDisplay(const bool display)
{
    display_ = display;
}