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
        { glm::vec3(-1.0f * scale, 0.0f, 0.0f), glm::vec3(scale, 0.0f, 0.0f) },
        Color::Red
    };
    
    Axis yAxis{
        { glm::vec3(0.0f, -1.0f * scale, 0.0f), glm::vec3(0.0f, scale, 0.0f) },
        Color::Green
    };
    
    genAxis(xAxis, m_xAxis, m_xAxisMaterial);
    genAxis(yAxis, m_yAxis, m_yAxisMaterial);
}

void Grid::genGrid(){
    
    //Generate Grid
    m_rectangle = new Rectangle();
    MeshGroup* gridMesh = m_rectangle->getMesh();
    gridMesh->setRotation(180.0f, 1.0f, 0.0f, 0.0f);
    gridMesh->setScale(m_scale, m_scale, m_scale);
    
    m_gridMaterial = new SolidMaterial(
                                   Color::Grey,
                                   std::string(ROOT_DIR + "Material/Shader/grid.vert"),
                                   std::string(ROOT_DIR + "Material/Shader/grid.frag")
                                );

    gridMesh->setMaterial(*m_gridMaterial);

    Shader* shader = m_gridMaterial->getShader();
    shader->setInt("division", m_division);
    shader->setFloat("gridScale", m_scale);
    shader->setFloat("thickness", m_thickness);
    
    m_mesh = gridMesh;
}

void Grid::genAxis(Axis axis, Points* model, SolidMaterial* material){
    //Generate Axis
    model = new Points(axis.Points);
    material = new SolidMaterial(axis.Color);
    
    MeshGroup* axisMesh = model->getMesh();
    axisMesh->setDrawMode(MeshBase::DrawMode::WIREFRAME);
    axisMesh->setMaterial(*material);
    
    //Transfer mesh to global mesh
    m_mesh->addChildren(axisMesh);
}
