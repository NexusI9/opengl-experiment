#version 330 core

in vec2 Uv;

layout(std140) uniform Camera{ //uniform block
    mat4 view;
    mat4 projection;
};

out vec4 outColor;

uniform vec3 color;
uniform int division;
uniform float gridScale;
uniform float thickness;

void main(){
    
    vec2 uv = Uv;
    vec4 color = vec4(color, 1.0);
    
    //Setup grid
    float patternSize = 1.0/division;   // size of the tile
    float edge = patternSize/thickness; // size of the edge
    float face_tone = 0.0; // 0.9 for the face of the tile
    float edge_tone = 1.0; // 0.5 for the edge
    
    vec2 gridUv = sign(vec2(edge) - mod(Uv, patternSize));
    vec4 pattern = vec4(face_tone - sign(gridUv.x + gridUv.y + 1.0) * (face_tone - edge_tone));

    //Setup gradient
    vec3 white = vec3(1.f);
    vec3 black = vec3(0.f);
    
    vec3 cam = view[3].xyz / gridScale;
    
    vec2 center = vec2(0.5f + (-1.0 * cam.x), 0.5f + (-1.0 * cam.x));
    float ray = min(distance(uv, center) * (gridScale / 10.0f), 1.0f);
    vec3 grad = mix(white, black, ray);
    
    outColor = color * pattern * vec4(grad, 0.0f);
}
