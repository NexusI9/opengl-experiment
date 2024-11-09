#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 uv;

uniform bool faceCamera;
uniform bool fixedSize;
uniform mat4 model;

layout(std140) uniform Camera{ //uniform block
    mat4 view;
    mat4 projection;
};



out vec2 Uv;

void main(){
    
    mat4 scaleMat = mat4(1.0f);
    if(fixedSize == true){
        float scale = length(view[3].xyz);
        scaleMat[0][0] = scale * model[0][0];
        scaleMat[1][1] = scale * model[1][1];
        scaleMat[2][2] = scale * model[2][2];
    }
    
    mat4 modelView =  view * model;
    
    if(faceCamera == true){
        
        // First colunm.
        modelView[0][0] = model[0][0];
        modelView[0][1] = 0.0;
        modelView[0][2] = 0.0;

        // Second colunm.
        modelView[1][0] = 0.0;
        modelView[1][1] = model[1][1];
        modelView[1][2] = 0.0;
        

        // Thrid colunm.
        modelView[2][0] = 0.0;
        modelView[2][1] = 0.0;
        modelView[2][2] = model[2][2];
        
    }
    
    
    Uv = uv;
    
    gl_PointSize = 6.0;
    gl_Position = projection * modelView * scaleMat * vec4(position, 1.0);
}
