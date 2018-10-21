#include "particleeffect.h"

ParticleEffect::ParticleEffect(){
    reset();
}

ParticleEffect::~ParticleEffect(){
    particles.clear();
}

void ParticleEffect::start() {
    qDebug() << "ParticleEffect::start. Particles count: " << particles.size() << endl;
    for (int i = 0; i < particles.size(); i++) {
        particles[i]->show();
    }
    active = true;
}

bool ParticleEffect::isActive() {
    return active;
}

void ParticleEffect::update() {
    if (!active) {
        return;
    }
    bool hasActiveParticle = false;
    for (int i = 0; i < particles.size(); i++) {
        particles[i]->update();
        if (particles[i]->isAlive()) {
            hasActiveParticle = true;
        }
    }
    if (!hasActiveParticle) {
        active = false;
        reset();
    }
}

void ParticleEffect::reset() {
    particles.clear();
    float velocity = 2.0;
    int stepSize = 360/particleCount;
    for (int i = 0; i < particleCount; i ++) {
        Particle *particle = new Particle();
        float dx = cos((3.14 * stepSize * i)/180) * 0.01;
        float dy = sin((3.14 * stepSize * i)/180) * 0.01;
        particle->setSize(particleSize);
        particle->initialize(xPos, yPos, dx, dy, velocity);
        particles.push_back(particle);
    }
}

void ParticleEffect::render(glm::mat4 &view, glm::mat4 &projection, glm::vec3 lightPos, glm::vec3 lightColor, ParticleShader *shader) {
    if(!active) {
        return;
    }
    for (int i = 0; i < particles.size(); i++) {
        particles[i]->render(view, projection, lightPos, lightColor, shader);
    }
}

