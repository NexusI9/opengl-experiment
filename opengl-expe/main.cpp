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
        0.0f, 0.5f,
        0.5f, 0.5f,
        -0.5f, 0.5f
    };
    
    const std::string vertexShaderPath = std::string(getenv("HOME"))+ std::string("/Documents/XCode/opengl/opengl-expe/Shader/triangle.vert");
    
    Primitive Triangle(triVertices, GL_STATIC_DRAW);
    Triangle.loadVertexShader(vertexShaderPath.c_str());
    Triangle.draw();
    
    
    window.draw();
    
    return 0;
}
