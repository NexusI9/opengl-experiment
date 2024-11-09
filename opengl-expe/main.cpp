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
#include "Material/DefaultMaterial.hpp"
#include "Material/Texture.hpp"

#include "Utility/Debugger.hpp"

const int WINDOW_WIDTH = 800, WINDOW_HEIGHT = 600;


int main(int argc, const char * argv[]) {
    
    //Setup Window
    Window window(WINDOW_WIDTH, WINDOW_HEIGHT, (std::string)"openGL Experiment");
    window.init();

    Scene scene;
    
    Camera camera({
        .fov = 45.0f,
        .ratio = (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT,
        .nearPlane = 0.1f,
        .farPlane = 100.0f,
        .bindingIndex = 0
    });
    
    //camera.translate(glm::vec3(2.0f, 2.0f, 2.0f));
    scene.setCamera(camera);
    
    Debugger::filterVerboseFlag(Verbose::Flag::MESH);
    
    //Draw cube
    Gltf cubeModel((std::string(ROOT_DIR+"Assets/Models/cube/cube.gltf")).c_str());
    MeshGroup* cubeMesh = cubeModel.getMesh();
    DefaultMaterial cubeMat;
    cubeMesh->setMaterial(cubeMat);
    cubeMesh->setScale(1.0f, 1.0f, 1.0f);
    cubeMesh->setPosition(2.0f, 3.0f, -1.0f);
    
    //Draw points
    std::vector<glm::vec3> pts{
        glm::vec3(0.3f, 2.0f, 3.0f),
        glm::vec3(1.0f, 3.4f, 2.0f),
        glm::vec3(-1.0f, 1.4f, -3.0f)
    };
    
    Debugger::drawPoints(pts, scene);

    scene.add(cubeMesh);
    
    scene.showGrid(true);

    window.draw(scene);
    
    return 0;
}
