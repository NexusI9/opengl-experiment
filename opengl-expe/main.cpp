//
//  main.cpp
//  opengl
//
//  Created by EL KHANTOUR Nassim on 31/08/2024.
//

#include <iostream>
#include <string>
#include <filesystem>
#include "Context/Window.hpp"
#include "Mesh/Primitive.hpp"


const int WINDOW_WIDTH = 800, WINDOW_HEIGHT = 600;


int main(int argc, const char * argv[]) {
    
    //Setup Window
    Window window(WINDOW_WIDTH, WINDOW_HEIGHT, (std::string)"openGL Experiment");
    window.init();
    
    //Setup Primitive Shape
    float triVertices[] = {
    //        POSITION                      COLOR
        -0.5f,  0.5f,   0.0f,       1.0f,   0.0f,   0.0f,
        0.5f,   0.5f,   0.0f,       0.0f,   1.0f,   0.0f,
        0.5f,   -0.5f,  0.0f,       0.0f,   0.0f,   1.0f,
        -0.5f,  -0.5f,  0.0f,       1.0f,   1.0f,   1.0f
    };
    
    GLuint triElements[] = {
        0,  1,  2,
        2,  3,  0
    };
    
    const std::string shaderBasePath =std::string(getenv("HOME"))+ std::string("/Documents/XCode/opengl/opengl-expe/Shader/triangle.");
    const std::string vertShaderPath = shaderBasePath+std::string("vert");
    const std::string fragShaderPath = shaderBasePath+std::string("frag");
    
    Primitive Triangle(triVertices, 4*6, triElements, 2*3);
    Triangle.loadVertexShader(vertShaderPath);
    Triangle.loadFragmentShader(fragShaderPath, "outColor");
    Triangle.buffer(GL_STATIC_DRAW);
    Triangle.shader.setAttributeFromBuffer("position", sizeof(float) * 6, NULL);
    Triangle.shader.setAttributeFromBuffer("color", sizeof(float) * 6, (void*)(3 * sizeof(float)));
    
    
    window.draw();
    
    return 0;
}
