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
#include "Model/Gltf.hpp"
#include "Mesh/MeshGroup.hpp"
#include "Material/BasicMaterial.hpp"


const int WINDOW_WIDTH = 800, WINDOW_HEIGHT = 600;


int main(int argc, const char * argv[]) {
    
    //Setup Window
    Window window(WINDOW_WIDTH, WINDOW_HEIGHT, (std::string)"openGL Experiment");
    window.init();

    Camera camera(45.0f, (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 100.0f, 0);
    camera.lookAt(glm::vec3(5.0f, 5.0f, 2.0f), glm::vec3(0.0f));
    //camera.translate(glm::vec3(0.0f, 0.0f, 0.0f));
    
    Gltf cubeModel((std::string(ROOT_DIR+"Assets/Models/cube/cube.gltf")).c_str());
    MeshGroup* cubeMesh = cubeModel.getMesh();
    BasicMaterial cubeMat;
    cubeMesh->setMaterial(cubeMat);
    
    Scene scene;
    scene.setCamera(camera);
    scene.add(cubeMesh);
    
    window.draw(scene);
    
    return 0;
}
