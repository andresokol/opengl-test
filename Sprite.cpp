//
// Created by sokol on 21.11.2016.
//

#include "Sprite.h"

Sprite::Sprite(const char *sceneFilePath, const glm::vec2& position) {
    _geometry.loadFromFile(sceneFilePath);
    _geometry.generateBuffers();
    _position = position;
}

void Sprite::draw() {
    _geometry.draw(glm::vec3(_position, 1.0f), (GLfloat)glfwGetTime() * 2.0f, glm::vec3(0, 0, 1.0f), true);
}

void Sprite::move(glm::vec2 moveVec) {
    _position += moveVec;
}