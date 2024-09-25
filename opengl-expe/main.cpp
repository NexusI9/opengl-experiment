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

#include "Mesh/Mesh.hpp"
#include "Mesh/Gltf.hpp"


const int WINDOW_WIDTH = 800, WINDOW_HEIGHT = 600;


int main(int argc, const char * argv[]) {
    
    //Setup Window
    Window window(WINDOW_WIDTH, WINDOW_HEIGHT, (std::string)"openGL Experiment");
    window.init();

    
    const std::string root = std::string(getenv("HOME"))+ std::string("/Documents/XCode/opengl/opengl-expe/");
    

    Gltf cube((root+std::string("Assets/Models/cube.gltf")).c_str());
    
    
    window.draw();
    
    return 0;
}
