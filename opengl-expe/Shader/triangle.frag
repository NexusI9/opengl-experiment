#version 330 core

in vec3 Color;
in vec2 Uv;

out vec4 outColor;

uniform sampler2D tex;

void main(){

    outColor = texture(tex, Uv);

}
