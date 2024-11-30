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
#include "Prefab/HexaGrid/HexaGrid.hpp"
#include "Model/Hexagon.hpp"

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
    
    //TODO: rewrite debug_log api
    Debugger::filterVerboseFlag(Verbose::Flag::MESH);
    
    scene.setCamera(camera);
    scene.showGrid(true);
    
    //Draw chunk
    Chunk chunk({
        .radius = 2.0f,
        .points = 24,
        .cliffDistance = 0.4f,
        .shoreDistance = 0.4f
    });
    
    Mesh* chunkMesh = chunk.getMesh();
    SolidMaterial mat({
        .color = Color::Grey,
        .vertexShader = std::string(ROOT_DIR + "Material/Shader/hexagrid.vert"),
        .fragmentShader = std::string(ROOT_DIR + "Material/Shader/hexagrid.frag"),
    });

    chunkMesh->setMaterial(mat);
    //chunkMesh->setScale(5.0f);
    
    //Draw hexa grid
    HexaGrid grid(glm::vec2(20.0f, 20.0f), 1.0f);
    Mesh* gridMesh = grid.getMesh();
    scene.add(gridMesh);
    
    /*
     Hexagon hexagon;
     Mesh* hexagonMesh = new Mesh({.name = "hex", .model = hexagon});
     hexagonMesh->setMaterial(mat);
     scene.add(hexagonMesh);
     */
    

    //scene.add(chunkMesh);
    
    window.draw(scene);
    
    return 0;
}
