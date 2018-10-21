#include "particle.h"

Particle::Particle() : xPos(0), yPos(0), dx(0.0), dy(0.0){
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    //normals
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
}

Particle::~Particle(){

}

void Particle::initialize(int x, int y, float inDx, float inDy, float vel){
    xPos = x;
    yPos = y;
    dx = inDx;
    dy = inDy;
    velocity = vel;
    alive = true;
}

void Particle::show(){
    visible = true;
}

void Particle::hide(){
    visible = false;
}

bool Particle::isAlive(){
    return alive;
}

void Particle::setSize(float s) {
    size = s;
}

void Particle::update(){
    if (alive) {
        float deltaX = (dx * velocity);
        float deltaY = (dy * velocity);
        xPos += deltaX;
        yPos += deltaY;
    }
}

void Particle::render(glm::mat4 &view, glm::mat4 &projection, glm::vec3 lightPos, glm::vec3 lightColor, ParticleShader *shader){
    if (visible && alive) {
        qDebug() << "Particle::render" << endl;
        glm::mat4 model = glm::mat4(1.0);
        model = glm::translate(model, glm::vec3(xPos, yPos, -10.0));
        model = glm::scale(model, glm::vec3(size, size, size));
        shader->use();
        shader->setMat4("model", model);
        shader->setMat4("view", view);
        shader->setMat4("projection", projection);
        shader->setVec3("objectColor", objectColor);
        shader->setVec3("lightPos", lightPos);
        shader->setVec3("lightColor", lightColor);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
}
