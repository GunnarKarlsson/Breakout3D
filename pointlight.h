#ifndef POINTLIGHT_H
#define POINTLIGHT_H

struct PointLight {
    glm::vec3 position;
    glm::vec3 ambient;
    glm::vec3 diffuse;
    float constant;
    float linear;
    float quadratic;
};

#endif // POINTLIGHT_H
