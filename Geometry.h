//
// Created by sokol on 18.11.2016.
//

#ifndef OPENGL_TEST_GEOMETRY_H
#define OPENGL_TEST_GEOMETRY_H

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>

class Geometry {
private:
    GLfloat* _verticesCoords;
    GLuint* _indices;
    GLuint _primitivesCount;
    GLuint _verticesCount;
    GLuint _coordsPerVertex;

    bool _hasTexture;
    GLuint _texture;

    GLuint _VAO, _VBO, _EBO;

    bool loadTexture(const char * texPath);
public:
    Geometry();

    ~Geometry();

    bool loadFromFile(const GLchar* filePath);
    void generateBuffers();

    void draw(bool unbindVAO);
};


#endif //OPENGL_TEST_GEOMETRY_H
