#ifndef PARTICLESHADER_H
#define PARTICLESHADER_H

#include "shader.h"

class ParticleShader : public Shader
{
public:
    ParticleShader();
    ~ParticleShader();
    const char* getShaderName();
    void compile();
};

#endif // PARTICLESHADER_H
