//
// Created by sokol on 18.11.2016.
//

#include "Geometry.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "SOIL.h"

Geometry::Geometry() {
    _verticesCoords = nullptr;
    _indices = nullptr;
    _verticesCount = 0;
    _primitivesCount = 0;
    _hasTexture = false;
    _coordsPerVertex = 6;
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

    geometryStream >> _verticesCount >> _primitivesCount >> _hasTexture;

    if (_hasTexture) {
        _coordsPerVertex = 8;
    }

    std::cout << _coordsPerVertex << std::endl;
    std::cout << _verticesCount << std::endl;
    std::cout << _primitivesCount << std::endl;

    _verticesCoords = new GLfloat[_verticesCount * _coordsPerVertex];
    _indices = new GLuint[_primitivesCount * 3];

    for (unsigned int i = 0; i < _verticesCount * _coordsPerVertex; ++i) {
        geometryStream >> _verticesCoords[i];
    }

    for (unsigned int i = 0; i < _primitivesCount; ++i) {
        geometryStream >> _indices[3 * i] >> _indices[3 * i + 1] >> _indices[3 * i + 2];
    }

    if (_hasTexture) {
        std::string texPath;
        geometryStream >> texPath;
        if (texPath == "") {
            std::cerr << "ERROR::TEXTURE_NOT_SET" << std::endl;
            return false;
        }
        std::cout << texPath << std::endl;
        return loadTexture(texPath.c_str());
    }

    return true;
}

void Geometry::generateBuffers() {
    glGenVertexArrays(1, &_VAO);
    glGenBuffers(1, &_VBO);
    glGenBuffers(1, &_EBO);

    glBindVertexArray(_VAO);

    glBindBuffer(GL_ARRAY_BUFFER, _VBO);
    glBufferData(GL_ARRAY_BUFFER, _verticesCount * _coordsPerVertex * sizeof(_verticesCoords[0]), _verticesCoords, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, _primitivesCount * 3 * sizeof(_indices[0]), _indices, GL_STATIC_DRAW);

    // Position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, _coordsPerVertex * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    // Color
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, _coordsPerVertex * sizeof(GLfloat), (GLvoid*) (3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    if(_hasTexture) {
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, _coordsPerVertex * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
        glEnableVertexAttribArray(2);
    }

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Note that this is allowed, the call to glVertexAttribPointer
    // registered VBO as the currently bound vertex buffer object
    // so afterwards we can safely unbind
    glBindVertexArray(0);
}

Geometry::~Geometry() {
    delete _verticesCoords;
    delete _indices;
    glDeleteVertexArrays(1, &_VAO);
    glDeleteBuffers(1, &_VBO);
}

void Geometry::draw(bool unbindVAO) {
    glBindVertexArray(_VAO);
    if(_hasTexture) glBindTexture(GL_TEXTURE_2D, _texture);
    glDrawElements(GL_TRIANGLES, 3 * _primitivesCount, GL_UNSIGNED_INT, 0);
    if (unbindVAO) glBindVertexArray(0);
}

bool Geometry::loadTexture(const char * texPath) {
    glGenTextures(1, &_texture);
    glBindTexture(GL_TEXTURE_2D, _texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width = 0,
        height = 0;

    unsigned char* image = SOIL_load_image(texPath, &width, &height, 0, SOIL_LOAD_RGBA);

    if (width == 0 || height == 0) {
        std::cerr << "ERROR::TEXTURE_NOT_LOADED" << std::endl;
        return false;
    }
    std::cout << width << "x" << height << std::endl;

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);

    SOIL_free_image_data(image);
    glBindTexture(GL_TEXTURE_2D, 0);
    return true;
}