#ifndef PARTICLEEFFECT_H
#define PARTICLEEFFECT_H

#include "common.h"
#include "particleshader.h"

class ParticleEffect
{
public:
    ParticleEffect();
    ~ParticleEffect();
    void start();
    bool isActive();
    void render(glm::mat4 &view, glm::mat4 &projection, glm::vec3 lightPos, glm::vec3 lightColor, ParticleShader *shader);
    void reset();
private:
    bool active = false;
};

#endif // PARTICLEEFFECT_H
