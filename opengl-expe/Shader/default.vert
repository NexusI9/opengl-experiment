#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 uv;

uniform mat4 model;

layout(std140) uniform Camera{ //uniform block
    mat4 view;
    mat4 projection;
};

out vec3 Position;
out vec3 Normal;
out vec3 Color;
out vec2 Uv;

void main(){
    
    Position = position;
    Uv = uv;
    Color = color;
    Normal = normal;

    // projection * view * model *
    gl_Position = model * vec4(position, 1.0);
}
