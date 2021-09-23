#ifndef PARTICLE_MANAGER_H_
#define PARTICLE_MANAGER_H_
#include <vector>
#include "Particle.h"
#include "Scene.h"

class ParticleManager
{
public:
    ParticleManager();
    ~ParticleManager();
    
    void Explosion(const sf::Vector2f position, Scene* scene);
};

#endif