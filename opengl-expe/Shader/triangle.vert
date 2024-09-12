#version 150 core


in vec2 position;
in vec3 color;
in vec2 uv;

out vec3 Color;
out vec2 Uv;

void main(){
    Uv = uv;
    Color = color;
    gl_Position = vec4(position, 0.0, 1.0);
}
