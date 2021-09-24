#ifndef BACKGROUND_H_
#define BACKGROUND_H_
#include "../Base/GameObject.h"
#include "BPMScene.h"

class Background : public GameObject
{
public:
    Background(BPMScene& scene, const sf::Vector2f& position);
    ~Background() override;
    void Update(float delta_time) override;
    void Draw(Camera& camera) const override;

private:
    BPMScene* scene_{nullptr};
};

#endif