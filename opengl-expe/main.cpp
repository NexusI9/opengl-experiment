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
        0.0f,   0.5f,   0.0f,
        0.5f,   -0.5f,  0.0f,
        -0.5f,  -0.5f,  0.0f
    };
    
    const std::string shaderBasePath =std::string(getenv("HOME"))+ std::string("/Documents/XCode/opengl/opengl-expe/Shader/triangle.");
    const std::string vertShaderPath = shaderBasePath+std::string("vert");
    const std::string fragShaderPath = shaderBasePath+std::string("frag");
    
    Primitive Triangle(triVertices, GL_STATIC_DRAW);
    Triangle.loadVertexShader(vertShaderPath.c_str(),"position");
    Triangle.loadFragmentShader(fragShaderPath.c_str(), "outColor");
    Triangle.draw();
    
    
    window.draw();
    
    return 0;
}
