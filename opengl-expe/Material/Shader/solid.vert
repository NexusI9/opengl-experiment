#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 uv;

uniform mat4 model;

layout(std140) uniform Camera{ //uniform block
    mat4 view;
    mat4 projection;
};

out vec2 Uv;

void main(){
    
    Uv = uv;
    
    gl_PointSize = 6.0;
    gl_Position = projection * view * model * vec4(position, 1.0);
}
