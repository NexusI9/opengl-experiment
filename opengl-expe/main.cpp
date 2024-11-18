//
//  main.cpp
//  opengl
//
//  Created by EL KHANTOUR Nassim on 31/08/2024.
//

#include <iostream>
#include <string>
#include <filesystem>

#include "Utility/Constant.h"
#include "Utility/Debugger.hpp"

#include "Context/Window.hpp"

#include "Scene/Camera.hpp"
#include "Scene/Scene.hpp"
#include "Material/SolidMaterial.hpp"

#include "Prefab/Island/Chunk.hpp"

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
    
    scene.setCamera(camera);
    
    Debugger::filterVerboseFlag(Verbose::Flag::MESH);
    
    Chunk chunk({
        .radius = 2.0f,
        .points = 24,
        .cliffDistance = 0.4f,
        .shoreDistance = 0.4f
    });
    
    MeshGroup* chunkMesh = chunk.getMesh();
    SolidMaterial mat({
        .color = Color::Grey
    });
    
    chunkMesh->setMaterial(mat);
    Debugger::drawVertex(chunk.getVertices(), scene, Color::Green, true);
    
    scene.add(chunkMesh);
    scene.showGrid(true);

    window.draw(scene);
    
    return 0;
}
