#version 330 core

layout (location = 0) in vec2 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 uv;

uniform mat4 model;

layout(std140) uniform Camera{ //uniform block
    mat4 view;
    mat4 projection;
};

out vec3 Color;
out vec2 Uv;

void main(){
    Uv = uv;
    Color = color;

    gl_Position =  projection * view * model * vec4(position, 0.0, 1.0);
}
