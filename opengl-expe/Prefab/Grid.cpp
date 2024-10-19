//
//  Grid.cpp
//  opengl-expe
//
//  Created by EL KHANTOUR Nassim on 17/10/2024.
//

#include "Grid.hpp"
#include "../Utility/Color.h"
#include "../Utility/Constant.h"


MeshGroup* Grid::getMesh(){
    
    m_rectangle = new Rectangle();
    MeshGroup* gridMesh = m_rectangle->getMesh();
    gridMesh->setRotation(180.0f, 1.0f, 0.0f, 0.0f);
    gridMesh->setScale(m_scale, m_scale, m_scale);
    
    m_material = new SolidMaterial(
                                   Color::Grey,
                                   std::string(ROOT_DIR + "Material/Shader/grid.vert"),
                                   std::string(ROOT_DIR + "Material/Shader/grid.frag")
                                );

    gridMesh->setMaterial(*m_material);

    Shader* shader = m_material->getShader();
    shader->setInt("division", m_division);
    shader->setFloat("gridScale", m_scale);
    shader->setFloat("thickness", m_thickness);
    
    return gridMesh;
}
