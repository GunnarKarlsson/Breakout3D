#include "skyboxshader.h"

SkyboxShader::SkyboxShader() : Shader() {}

SkyboxShader::~SkyboxShader() {}

const char* SkyboxShader::getShaderName() {
    return "Skybox Shader";
}

void SkyboxShader::compile() {
    Shader::compile(":/shaders/skybox.vert", ":/shaders/skybox.frag");
}
