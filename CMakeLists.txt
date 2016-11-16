cmake_minimum_required(VERSION 3.5)
project(opengl_test)

set(EXTERNAL_LIBRARIES_PATH ${CMAKE_HOME_DIRECTORY}/libraries)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra")

find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIRS})
link_directories(${OpenGL_LIBRARY_DIRS})
add_definitions(${OpenGL_DEFINITIONS})
if(NOT OPENGL_FOUND)
    message(ERROR " OPENGL not found!")
endif(NOT OPENGL_FOUND)

message(WARNING ${EXTERNAL_LIBRARIES_PATH})
include_directories(${EXTERNAL_LIBRARIES_PATH}/include)

set(EXTERNAL_LIBS
            ${OPENGL_LIBRARIES}
            ${EXTERNAL_LIBRARIES_PATH}/lib/libglfw3.a
            ${EXTERNAL_LIBRARIES_PATH}/lib/glew32.dll
        )

set(SOURCE_FILES main.cpp Shader.cpp Shader.h)
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} PRIVATE ${EXTERNAL_LIBS})
