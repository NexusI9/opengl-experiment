#version 150 core


in vec2 position;
in vec3 color;
in vec2 uv;

out vec3 Color;
out vec2 Uv;

uniform mat4 transform;

void main(){
    Uv = uv;
    Color = color;
    
    gl_Position = transform * vec4(position, 0.0, 1.0);
}
