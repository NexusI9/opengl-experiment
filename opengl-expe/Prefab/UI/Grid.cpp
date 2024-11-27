//
//  Grid.cpp
//  opengl-expe
//
//  Created by EL KHANTOUR Nassim on 17/10/2024.
//

#include "Grid.hpp"
#include "../../Utility/Color.h"
#include "../../Utility/Constant.h"


Grid::Grid(float scale, int division, float thickness) : m_scale(scale), m_division(division), m_thickness(thickness){
    genGrid();
}

void Grid::genGrid(){
    
    //Generate Grid
    Rectangle rectangle;
    m_mesh = new Mesh({.name = "grid", .model = rectangle});
    m_mesh->setScale(m_scale, m_scale, m_scale);
    
    SolidMaterial gridMaterial({
                    .color = glm::vec3(0.2f),
                    .vertexShader = std::string(ROOT_DIR + "Material/Shader/grid.vert"),
                    .fragmentShader = std::string(ROOT_DIR + "Material/Shader/grid.frag"),
                    .uniforms = {
                       {.name = "division",  .type = UniformType::INT,    .value = m_division  },
                       {.name = "gridScale", .type = UniformType::FLOAT,  .value = m_scale     },
                       {.name = "thickness", .type = UniformType::FLOAT,  .value = m_thickness }
                    }
    });

    m_mesh->setMaterial(gridMaterial);
}

