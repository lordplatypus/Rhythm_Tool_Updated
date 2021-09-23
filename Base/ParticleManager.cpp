#include <SFML/Graphics.hpp>
#include "LP.h"
#include "ParticleManager.h"
#include "ID.h"
#include "Math.h"

ParticleManager::ParticleManager()
{}

ParticleManager::~ParticleManager()
{}

void ParticleManager::Explosion(const sf::Vector2f position, Scene* scene)
{//Example
    // for (int i = 0; i < 50; i++)
    // {
    //     sf::Sprite key = LP::SetSprite(smoke_texture);
    //     LP::SetSpriteOriginCenter(&key);
    //     float lifespan = (rand() % 5 + 5) / 10.0f;
    //     float angle = (rand() % 360) * (M_PI / 180);
    //     float speed = rand() % 50 + 30;
    //     float vx = (float)cos(angle) * speed;
    //     float vy = (float)sin(angle) * speed;
    //     float endScale = (rand() % 2 + 1) / 10.0f;
    //     float startAlpha = rand() % 256;

    //     scene->AddGameObject(new Particle(key, position.x, position.y, vx, vy, 1, lifespan, 0, -100.0f, 0, 0, .05f, endScale, 255, 255, 255, startAlpha, 0));
    // }

    // for (int i = 0; i < 100; i++)
    // {
    //     sf::Sprite key = LP::SetSprite(fire_texture);
    //     LP::SetSpriteOriginCenter(&key);
    //     float lifespan = (rand() % 5 + 1) / 10.0f;
    //     float angle = (rand() % 360) * (M_PI / 180);
    //     float speed = rand() % 50 + 30;
    //     float vx = (float)cos(angle) * speed;
    //     float vy = (float)sin(angle) * speed;
    //     float endScale = (rand() % 2 + 1) / 10.0f;
    //     float startAlpha = rand() % 256;

    //     scene->AddGameObject(new Particle(key, position.x, position.y, vx, vy, 1, lifespan, 0, 0, 0, 0, .05f, endScale, 255, 255, 255, startAlpha, 0));
    // }
}