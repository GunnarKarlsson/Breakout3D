#include "basicshader.h"


BasicShader::BasicShader() : Shader() {}

BasicShader::~BasicShader() {}

const char* BasicShader::getShaderName() {
    return "Basic Shader";
}

void BasicShader::compile() {
    Shader::compile(":/shaders/basic.vert", ":/shaders/basic.frag");
}
