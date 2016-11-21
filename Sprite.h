//
// Created by sokol on 21.11.2016.
//

#ifndef OPENGL_TEST_SPRITE_H
#define OPENGL_TEST_SPRITE_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Geometry.h"

class Sprite {
private:
    Geometry _geometry;
    glm::vec2 _position;

public:
    Sprite(const char * sceneFilePath, const glm::vec2& position);

    void draw();
    void move(glm::vec2 moveVec);
};


#endif //OPENGL_TEST_SPRITE_H
