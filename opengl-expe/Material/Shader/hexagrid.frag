#version 330 core

out vec4 outColor;

in vec3 vColor;

void main(){
    
    float l = smoothstep(0.95f, 1.0f, vColor.r);
    vec3 color = vec3(l);
    
    outColor = vec4(color, color.r);
}
