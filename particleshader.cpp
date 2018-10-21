#include "particleshader.h"

ParticleShader::ParticleShader() : Shader() {}

ParticleShader::~ParticleShader() {}

const char* ParticleShader::getShaderName() {
    return "Particle Shader";
}

void ParticleShader::compile() {
    Shader::compile(":/Shaders/particle.vert",":/Shaders/particle.frag");
}
