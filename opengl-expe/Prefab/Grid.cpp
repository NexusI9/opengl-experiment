//
//  Grid.cpp
//  opengl-expe
//
//  Created by EL KHANTOUR Nassim on 17/10/2024.
//

#include "Grid.hpp"
#include "../Utility/Color.h"
#include "../Utility/Constant.h"


Grid::Grid(float scale, int division, float thickness) : m_scale(scale), m_division(division), m_thickness(thickness){
    
    genGrid();
    
    Axis xAxis{
        .points = { glm::vec3(-1.0f * scale, 0.0f, 0.0f), glm::vec3(scale, 0.0f, 0.0f) },
        .color = Color::Red
    };
    
    Axis yAxis{
        .points = { glm::vec3(0.0f, -1.0f * scale, 0.0f), glm::vec3(0.0f, scale, 0.0f) },
        .color = Color::Green
    };
    
    genAxis(xAxis);
    genAxis(yAxis);
}

void Grid::genGrid(){
    
    //Generate Grid
    Rectangle rectangle;
    MeshGroup* gridMesh = rectangle.getMesh();
    gridMesh->setScale(m_scale, m_scale, m_scale);
    
    SolidMaterial gridMaterial({
                   .color = Color::Grey,
                   .vertexShader = std::string(ROOT_DIR + "Material/Shader/grid.vert"),
                   .fragmentShader = std::string(ROOT_DIR + "Material/Shader/grid.frag"),
                   .uniforms = {
                       {.name = "division",  .type = UniformType::INT,    .value = m_division  },
                       {.name = "gridScale", .type = UniformType::FLOAT,  .value = m_scale     },
                       {.name = "thickness", .type = UniformType::FLOAT,  .value = m_thickness }
                   }
    });

    
    gridMesh->setMaterial(gridMaterial);
    m_mesh = gridMesh;
}

void Grid::genAxis(Axis& axis){
    
    //Generate Axis
    Points points(axis.points);
    SolidMaterial material({
        .color = axis.color,
        .vertexShader = std::string(ROOT_DIR + "Material/Shader/solid.vert"),
        .fragmentShader = std::string(ROOT_DIR + "Material/Shader/solid.frag"),
    });
    
    MeshGroup* axisMesh = points.getMesh();
    axisMesh->setDrawMode(MeshBase::DrawMode::WIREFRAME);
    axisMesh->setMaterial(material);
    
    //Transfer mesh to global mesh
    m_mesh->addChildren(axisMesh);
    
}
