#version 330 core

in vec3 Position;
in vec3 Normal;
in vec3 Color;
in vec2 Uv;

out vec4 outColor;

uniform sampler2D texture0;

void main(){
    outColor = texture(texture0, Uv) * vec4(1.0f,1.0f,1.0f, 1.0f);
}
