#include "particleeffect.h"

ParticleEffect::ParticleEffect(){}

ParticleEffect::~ParticleEffect(){}

void ParticleEffect::start() {

}

bool ParticleEffect::isActive() {
    return active;
}

void ParticleEffect::reset() {

}

void ParticleEffect::render(glm::mat4 &view, glm::mat4 &projection, glm::vec3 lightPos, glm::vec3 lightColor, ParticleShader *shader) {

}

