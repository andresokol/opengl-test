//
// Created by sokol on 18.11.2016.
//

#include "Geometry.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

Geometry::Geometry() {
    _vertices = nullptr;
    _indices = nullptr;
    _verticesCount = 0;
    _primitivesCount = 0;
}

bool Geometry::loadFromFile(const GLchar *filePath) {
    std::ifstream geometryFile;
    std::stringstream geometryStream;

    geometryFile.exceptions(std::ifstream::badbit);

    try {
        geometryFile.open(filePath);

        geometryStream << geometryFile.rdbuf();
        geometryFile.close();
    }
    catch(std::ifstream::failure e) {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
        return false;
    }

    geometryStream >> _verticesCount >> _primitivesCount;
    _vertices = new GLfloat[_verticesCount];
    _indices = new GLuint[_primitivesCount * 3];

    for (unsigned int i = 0; i < _verticesCount; ++i) {
        geometryStream >> _vertices[i];
    }

    for (unsigned int i = 0; i < _primitivesCount; ++i) {
        geometryStream >> _indices[3 * i] >> _indices[3 * i + 1] >> _indices[3 * i + 2];
    }

    return true;
}

void Geometry::generateBuffers() {
    glGenVertexArrays(1, &_VAO);
    glGenBuffers(1, &_VBO);
    glGenBuffers(1, &_EBO);

    glBindVertexArray(_VAO);

    glBindBuffer(GL_ARRAY_BUFFER, _VBO);
    glBufferData(GL_ARRAY_BUFFER, _verticesCount * sizeof(_vertices[0]), _vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, _primitivesCount * 3 * sizeof(_indices[0]), _indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Note that this is allowed, the call to glVertexAttribPointer
    // registered VBO as the currently bound vertex buffer object
    // so afterwards we can safely unbind
    glBindVertexArray(0);
}

Geometry::~Geometry() {
    delete _vertices;
    delete _indices;
}

void Geometry::draw(bool unbindVAO) {
    glBindVertexArray(_VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    if (unbindVAO) glBindVertexArray(0);
}