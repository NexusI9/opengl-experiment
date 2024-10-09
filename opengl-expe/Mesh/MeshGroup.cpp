//
//  MeshGroup.cpp
//  opengl-expe
//
//  Created by EL KHANTOUR Nassim on 07/10/2024.
//

#include "MeshGroup.hpp"


void MeshGroup::draw(Camera& camera){
    for(Mesh& mesh : m_meshes) mesh.draw(camera);
}

void MeshGroup::setMaterial(Material& material){
    for(Mesh& mesh : m_meshes) mesh.setMaterial(material);
}

void MeshGroup::setDrawMode(DrawMode mode){
    for(Mesh& mesh : m_meshes) mesh.setDrawMode(mode);
}
