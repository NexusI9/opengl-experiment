#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 uv;

uniform mat4 model;
uniform float gridScale;

layout(std140) uniform Camera{ //uniform block
    mat4 view;
    mat4 projection;
    vec4 camPosition;
};

out vec2 Uv;

void main(){
    Uv = uv;
    
    //Set grid position to camera position
    mat4 fixModel = model;
    fixModel[3].x = camPosition.x;
    fixModel[3].y = camPosition.y;
    
    gl_Position = projection * view * fixModel * vec4(position, 1.0);
}
