#version 330 core

out vec4 outColor;

uniform vec3 color;
uniform sampler2D texture0;

in vec2 Uv;

void main(){
    
    vec4 tex = texture(texture0, Uv);
    outColor = tex.r * vec4(color, 1.0f);
    //outColor = vec4(vec3(tex.r), 1.0f);
}
