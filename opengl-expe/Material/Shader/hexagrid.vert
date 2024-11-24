#use 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 uv;
layout (location = 4) in vec2 worldCoordinate;

uniform mat4 model;

layout(std140) uniform Camera{ //uniform block
    mat4 view;
    mat4 projection;
    vec4 camPosition;
};


void main(){
    
    gl_Position = projection * view * model * vec4(position, 1.0);
}
