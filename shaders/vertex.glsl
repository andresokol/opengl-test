#version 330 core

layout (location = 0) in vec3 position;

out vec4 gl_Position;

void main()
{
    gl_Position = vec4(position.xyz, 1.0f);
}
