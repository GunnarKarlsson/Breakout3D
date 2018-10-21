#ifndef PARTICLEEFFECT_H
#define PARTICLEEFFECT_H

#include <ctime>
#include "common.h"
#include "particleshader.h"
#include "particle.h"

class ParticleEffect
{
public:
    ParticleEffect();
    ~ParticleEffect();
    void setPosition(int x, int y);
    void start();
    bool isActive();
    void update();
    void render(glm::mat4 &view, glm::mat4 &projection, glm::vec3 lightPos, glm::vec3 lightColor, ParticleShader *shader);
    void reset();
private:
    std::clock_t clockStart;
    const double durationLimit = 50000;
    double duration;
    int xPos = 0;
    int yPos = 0;
    int particleCount = 36;
    float particleSize = 0.2;
    bool active = false;
    std::vector<Particle*> particles;
};

#endif // PARTICLEEFFECT_H
