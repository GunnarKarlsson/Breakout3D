#include "entity.h"

Entity::Entity()
{

    xPos = 0;
    yPos = 0;
    dx = 0;
    dy = 0;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
}

Entity::~Entity() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void Entity::setTextureId(unsigned int &id) {
    textureId = id;
}

void Entity::setVelocity(int velocity) {
    this->velocity = velocity;
}

void Entity::setSize(int size) {
    this->size =  size;
}

void Entity::render(glm::mat4 &view, glm::mat4 &projection, Shader *shader) {
    if (visible) {
    glm::mat4 model = glm::mat4(1.0);
    model = glm::translate(model, glm::vec3(xPos, yPos, -1.0));
    shader->use();
    shader->setMat4("model", model);
    shader->setMat4("view", view);
    shader->setMat4("projection", projection);

    glBindTexture(GL_TEXTURE_2D, textureId);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    }
}

void Entity::initialize(float x, float y, float inDx, float inDy) {
    xPos = x;
    yPos = y;
    dx = inDx;
    dy = inDy;
    visible = true;
}

void Entity::update() {
    xPos += (dx * velocity);
    yPos += (dy * velocity);
}

void Entity::update(int minX, int minY, int maxX, int maxY) {

    xPos += (dx * velocity);
    yPos += (dy * velocity);

    if (xPos < (minX + size/2)) {
        dx *=-1.0;
    }

    if (yPos < (minY + size/2)) {
        dy *= -1.0;
    }

    if (xPos > (maxX - size/2)) {
        dx *=-1.0;
    }

    if (yPos > (maxY -  size/2)) {
        dy *= -1.0;
    }
}


bool Entity::isVisible() {
    return visible;
}

