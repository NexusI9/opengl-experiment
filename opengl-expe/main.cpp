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

#include "./Utility/Constant.h"

#include "Scene/Camera.hpp"
#include "Scene/Scene.hpp"
#include "Mesh/Gltf.hpp"


const int WINDOW_WIDTH = 800, WINDOW_HEIGHT = 600;


int main(int argc, const char * argv[]) {
    
    //Setup Window
    Window window(WINDOW_WIDTH, WINDOW_HEIGHT, (std::string)"openGL Experiment");
    window.init();

    Camera camera(45.0f, (float) WINDOW_WIDTH / WINDOW_HEIGHT, 1.0f, 10.0f, 0);
    camera.lookAt(glm::vec3(2.2f, 1.2f, 1.2f), glm::vec3(0.0f));
    //camera.translate(glm::vec3(0.0f, 2.0f, 0.0f));
    
    Gltf cube((ROOT_DIR+std::string("Assets/Models/cube.gltf")).c_str());
    
    Scene scene;
    scene.add(&cube);
    
    window.draw(scene);
    
    return 0;
}
