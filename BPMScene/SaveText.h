#ifndef SAVE_TEXT_H_
#define SAVE_TEXT_H_
#include "../Base/GameObject.h"
#include "BPMScene.h"

class SaveText : public GameObject
{
public:
    SaveText(BPMScene& scene, const sf::Vector2f& position, const std::string& BPMFilePath);
    ~SaveText() override;
    void Update(float delta_time) override;
    void Draw(Camera& camera) const override;

private:
    BPMScene* scene_{nullptr};
    sf::Text saveText_; //the save text
    float alpha_{255.0f}; //alpha for the text object
    float speed_{100.0f}; //speed at which the object fades
};

#endif