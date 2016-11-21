#include <iostream>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Shader.h"
#include "Geometry.h"

#define FRAGMENT_SHADER_PATH "d:/code/opengl-test/shaders/fragment.glsl"
#define VERTEX_SHADER_PATH "d:/code/opengl-test/shaders/vertex.glsl"

#define GEOMETRY_PATH "d:/code/opengl-test/scene/rectangle.scene"
#define SECONDARY_GEOMETRY_PATH "d:/code/opengl-test/scene/small_triangle.scene"

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

GLFWwindow* initializeGLFW() {
    // Init GLFW
    glfwInit();

    // Set up GLFW
    // Set minimal required OpenGL version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    // Set up profile
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Make window resizable
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    // Create window object
    GLFWwindow* window = glfwCreateWindow(800, 600, "Hello, World!", nullptr, nullptr);
    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return nullptr;
    }
    glfwMakeContextCurrent(window);

    return window;
}

int main() {
    GLFWwindow* window = initializeGLFW();
    if (window == nullptr) return -1;

    // Init GLEW
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return -1;
    }

    // Passing window size to OpenGL
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);

    // Pass key press handler to GLFW
    glfwSetKeyCallback(window, key_callback);

    // --------- SHADERS --------------

    Shader shader = Shader(VERTEX_SHADER_PATH, FRAGMENT_SHADER_PATH);

    // --------------------------------

    // --------- SCENE ----------------

    Geometry geometry;
    if(!geometry.loadFromFile(GEOMETRY_PATH)) {
        std::cout << "ERROR::GEOMETRY_NOT_LOADED";
    }
    geometry.generateBuffers();

    Geometry geometry2;
    if(!geometry2.loadFromFile(SECONDARY_GEOMETRY_PATH)) {
        std::cout << "ERROR::GEOMETRY_NOT_LOADED";
    }
    geometry2.generateBuffers();

    // Game loop while no 'close window' signal recieved
    while(!glfwWindowShouldClose(window))
    {
        // check for events (eg key pressed)
        glfwPollEvents();

        // fill background color
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // draw to buffer
        shader.use();
        geometry.draw(true);
        geometry2.draw(true);

        // update picture
        glfwSwapBuffers(window);
    }

    // release resources
    glfwTerminate();

    return 0;
}


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
    std::cout << key << " " << scancode << std::endl;

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}
