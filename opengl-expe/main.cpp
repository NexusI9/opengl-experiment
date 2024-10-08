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

#include "Utility/Transform.hpp"
#include "Utility/Clock.hpp"

#include "Scene/Camera.hpp"

#include "Mesh/Primitive.hpp"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>

const int WINDOW_WIDTH = 800, WINDOW_HEIGHT = 600;


int main(int argc, const char * argv[]) {
    
    //Setup Window
    Window window(WINDOW_WIDTH, WINDOW_HEIGHT, (std::string)"openGL Experiment");
    window.init();
    
    //Setup Primitive Shape
    float triVertices[] = {
    //        POSITION                      COLOR                   UV
        -0.5f,  0.5f,   0.0f,       1.0f,   0.0f,   0.0f,       0.0f,   0.0f,
        0.5f,   0.5f,   0.0f,       0.0f,   1.0f,   0.0f,       1.0f,   0.0f,
        0.5f,   -0.5f,  0.0f,       0.0f,   0.0f,   1.0f,       1.0f,   1.0f,
        -0.5f,  -0.5f,  0.0f,       1.0f,   1.0f,   1.0f,       0.0f,   1.0f
    };
    
    GLuint triElements[] = {
        0,  1,  2,
        2,  3,  0
    };
    
    const std::string root = std::string(getenv("HOME"))+ std::string("/Documents/XCode/opengl/opengl-expe/");
    
    const std::string shaderBasePath = root + std::string("Shader/triangle.");
    const std::string vertShaderPath = shaderBasePath+std::string("vert");
    const std::string fragShaderPath = shaderBasePath+std::string("frag");
    
    const std::string checkerPath = root+std::string("Assets/Textures/uvchecker.png");
    
    Primitive Plane(triVertices, 4*8, triElements, 2*3);
    Plane.buffer(GL_STATIC_DRAW);
    Plane.loadShader(vertShaderPath, fragShaderPath, "outColor");
    Plane.loadTexture(checkerPath, 1024, 1024, 0);
    
    Plane.shader->setAttribute("position", 3, sizeof(float) * 8, NULL);
    Plane.shader->setAttribute("color", 3, sizeof(float) * 8, (void*)(3 * sizeof(float)));
    Plane.shader->setAttribute("uv", 2, sizeof(float) * 8, (void*)(6*sizeof(float)));
    Plane.shader->setSampler2D("tex", 0);
    
    //Camera
    Camera camera(40.0f, (float)(WINDOW_WIDTH/WINDOW_HEIGHT), 1.0f, 10.0f, 0);
    camera.lookAt(glm::vec3(2.2f, 1.2f, 1.2f), glm::vec3(0.0f));
    
    glm::mat4 rotate = Transform::rotate(45.0f, 0.0f, 0.0f, 1.0f);
    Plane.shader->setMatrix4("model", rotate);
    Plane.shader->setUniformBlock("Camera", camera.getMatrixBindingIndex());
    
    window.draw();
    
    return 0;
}
