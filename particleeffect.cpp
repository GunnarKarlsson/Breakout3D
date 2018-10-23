#include "particleeffect.h"
#include <random>

ParticleEffect::ParticleEffect(){

   pointLight.position = glm::vec3(0.0,2.0,-7.0);
   pointLight.ambient = glm::vec3(0.0, 1.0, 5.0);
   pointLight.constant = 1.0f;
   pointLight.linear = 0.09f;
   pointLight.quadratic = 0.032;
   pointLight.isOn = false;
   pointLight.intensity = 1.0;

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

PointLight ParticleEffect::getPointLight() const {
    return pointLight;
}

void ParticleEffect::setPosition(int x, int y) {
    xPos = x;
    yPos = y;
    pointLight.position = glm::vec3(xPos, yPos, -9.0);
}

void ParticleEffect::start() {
    pointLight.isOn = true;
    qDebug() << "ParticleEffect::start. Particles count: " << particles.size() << endl;
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
    pointLight.isOn = false;
}

void ParticleEffect::render(glm::mat4 &view, glm::mat4 &projection, glm::vec3 lightPos, glm::vec3 lightColor, ParticleShader *shader) {
    if(!active) {
        return;
    }
    for (int i = 0; i < particles.size(); i++) {
        particles[i]->render(view, projection, lightPos, lightColor, shader);
    }
}

