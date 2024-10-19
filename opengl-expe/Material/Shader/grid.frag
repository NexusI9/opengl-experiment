#version 330 core

in vec2 Uv;

out vec4 outColor;

uniform vec3 color;
uniform int division;
uniform float thickness;

void main(){
    
    vec2 uv = Uv;
    float size = 1.0/division;   // size of the tile
    float edge = size/thickness; // size of the edge
    float face_tone = 0.0; // 0.9 for the face of the tile
    float edge_tone = 1.0; // 0.5 for the edge
    
    uv = sign(vec2(edge) - mod(Uv, size));
    vec4 pattern = vec4(face_tone - sign(uv.x + uv.y + 1.0) * (face_tone - edge_tone));
    vec4 color = vec4(color, 1.0);
    outColor = color * pattern;
}
