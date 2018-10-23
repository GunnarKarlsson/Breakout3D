#include "particleeffect.h"
#include <random>

ParticleEffect::ParticleEffect(){
   reset();
}

ParticleEffect::~ParticleEffect(){
    particles.clear();
}

float ParticleEffect::getIntensity() {
    if (isActive()) {
        if (duration < durationLimit/5) {
            intensity += 0.05;
            if (intensity > 0.7) {
                intensity = 0.7;
            }
        } else if (intensity > 0.0){
            intensity -= 0.05;
            if (intensity < 0.0) {
                intensity = 0.0;
            }
        }
    } else {
        intensity = 0.0;
    }
    return intensity;
}

glm::vec3 ParticleEffect::getPointLightPosition() const {
    return pointLightPosition;
}

void ParticleEffect::setPosition(int x, int y) {
    xPos = x;
    yPos = y;
    pointLightPosition = glm::vec3(xPos, yPos, -9.0);
}

void ParticleEffect::start() {
    pointLightIsOn = true;
    for (int i = 0; i < particles.size(); i++) {
        particles[i]->show();
    }
    active = true;
    clockStart = std::clock();
    intensity = 0.0;
}

bool ParticleEffect::isActive() {
    return active;
}

void ParticleEffect::update() {
    if (!active) {
        return;
    }

    bool durationLimitReached = false;
    duration = ( std::clock() - clockStart );
    if (duration >= durationLimit) {
        durationLimitReached = true;
    }

    bool hasActiveParticle = false;
    for (int i = 0; i < particles.size(); i++) {
        particles[i]->update();


        if (particles[i]->isAlive()) {
            hasActiveParticle = true;
        }
    }
    if (!hasActiveParticle || durationLimitReached) {
        active = false;
        reset();
    }
}

void ParticleEffect::reset() {
    clockStart = 0.0;
    particles.clear();
    float velocity = 4.0;
    int stepSize = 360/particleCount;
    int n = 1800;
    for (int i = 0; i < particleCount; i ++) {
        Particle *particle = new Particle();
        float dx = float(rand() % n - n/2)/(n*10);
        float dy = float(rand() % n - n/2)/(n*10);
        float dz = float(rand() % n - n/2)/(n*10);
        particle->setSize(particleSize);
        particle->initialize(xPos, yPos, dx, dy, dz, velocity);
        particles.push_back(particle);
    }
    pointLightIsOn = false;
}

void ParticleEffect::render(glm::mat4 &view, glm::mat4 &projection, glm::vec3 lightPos, glm::vec3 lightColor, ParticleShader *shader) {
    if(!active) {
        return;
    }
    for (int i = 0; i < particles.size(); i++) {
        particles[i]->render(view, projection, lightPos, lightColor, shader);
    }
}

