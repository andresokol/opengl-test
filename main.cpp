#include <iostream>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "Geometry.h"
#include "Sprite.h"

#define FRAGMENT_SHADER_PATH "d:/code/opengl-test/shaders/fragment.glsl"
#define VERTEX_SHADER_PATH "d:/code/opengl-test/shaders/vertex.glsl"

#define GEOMETRY_PATH "d:/code/opengl-test/scene/rectangle.scene"
#define SECONDARY_GEOMETRY_PATH "d:/code/opengl-test/scene/small_triangle.scene"

const GLuint WINDOW_WIDTH = 800,
             WINDOW_HEIGHT = 600;
const double GAME_TICK = 1.0f / 60;

bool KEY_STATE[350];

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
    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Hello, World!", nullptr, nullptr);
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

    // Enable alpha channel
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // --------- SHADERS --------------

    Shader::loadFromFile(VERTEX_SHADER_PATH, FRAGMENT_SHADER_PATH);

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

    Sprite sDafuqman("d:/code/opengl-test/scene/dafuq_man.sprite", glm::vec2(0.5f, 0.5f));

    GLfloat timePreviousTick = 0;
    // Game loop while no 'close window' signal recieved
    while(!glfwWindowShouldClose(window))
    {
        GLfloat timeNow = glfwGetTime();
        if (timeNow - timePreviousTick < GAME_TICK) continue;
        timePreviousTick = timeNow;

        // check for events (eg key pressed)
        glfwPollEvents();
        if(KEY_STATE[GLFW_KEY_W]) {
            sDafuqman.move(glm::vec2(0.01f, 0.0f));
        }
        if(KEY_STATE[GLFW_KEY_S]) {
            sDafuqman.move(glm::vec2(-0.01f, 0.0f));
        }
        if(KEY_STATE[GLFW_KEY_D]) {
            sDafuqman.move(glm::vec2(0.0f, 0.01f));
        }
        if(KEY_STATE[GLFW_KEY_A]) {
            sDafuqman.move(glm::vec2(0.0f, -0.01f));
        }

        // fill background color
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        sDafuqman.draw();

        // update picture
        glfwSwapBuffers(window);
    }

    // release resources
    glfwTerminate();

    return 0;
}


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
    if (action == GLFW_PRESS && key != GLFW_KEY_UNKNOWN) {
        KEY_STATE[key] = true;
    }
    else if (action == GLFW_RELEASE && key != GLFW_KEY_UNKNOWN) {
        KEY_STATE[key] = false;
    }

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}
