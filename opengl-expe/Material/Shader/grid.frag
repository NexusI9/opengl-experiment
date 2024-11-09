#version 330 core

in vec2 Uv;

layout(std140) uniform Camera{ //uniform block
    mat4 view;
    mat4 projection;
    vec4 camPosition;
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
    
    //Move Uv to the opposite camera direction to compensate the grid translation
    vec2 compensUv = vec2(Uv.x + camPosition.x * patternSize, Uv.y - camPosition.y * patternSize);
    
    vec2 gridUv = sign(vec2(edge) - mod(compensUv, patternSize));
    vec4 pattern = vec4(face_tone - sign(gridUv.x + gridUv.y + 1.0) * (face_tone - edge_tone));

    vec2 center = vec2(0.5f, 0.5f);
    vec3 white = vec3(1.f);
    vec3 black = vec3(0.f);
    vec3 red = vec3(1.f,0.f,0.f);
    vec3 green = vec3(0.f,1.f,0.f);
    
    //Add X & Y Axis
    float axisThickness = 0.04f / gridScale;
    float xAxis = step(abs(compensUv.x - center.x), axisThickness);
    float yAxis = step(abs(compensUv.y - center.y), axisThickness);
    vec3 xAxisColor = mix(black, red, vec3(xAxis));
    vec3 yAxisColor = mix(black, green, vec3(yAxis));
    vec3 axis = max(xAxisColor, yAxisColor); //combine axis

    vec4 axisMask = vec4(min(1.0f - xAxis, 1.0f - yAxis));
    
    //Setup gradient
    float fadeFactor = max(100.0f / length(camPosition.z), 50.0f);
    float ray = min(distance(uv, center) * gridScale / fadeFactor, 1.0f);
    vec3 grad = mix(white, black, ray);
    
    outColor = (color * pattern * axisMask + vec4(vec3(axis), axis)) * vec4(grad, 0.0f);
}
