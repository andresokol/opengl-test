//
// Created by sokol on 16.11.2016.
//

#ifndef OPENGL_TEST_SHADER_H
#define OPENGL_TEST_SHADER_H

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader {
private:
    GLuint program;
public:
    Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
    void use();
};

#endif //OPENGL_TEST_SHADER_H
