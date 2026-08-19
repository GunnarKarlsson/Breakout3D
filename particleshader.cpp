#include "particleshader.h"

ParticleShader::ParticleShader() : Shader() {}

ParticleShader::~ParticleShader() {}

const char* ParticleShader::getShaderName() {
    return "Particle Shader";
}

void ParticleShader::compile() {
    Shader::compile(":/shaders/particle.vert",":/shaders/particle.frag");
}
