//
//  MeshGroup.cpp
//  opengl-expe
//
//  Created by EL KHANTOUR Nassim on 07/10/2024.
//

#include "MeshGroup.hpp"
#include "../Utility/Transform.hpp"

void MeshGroup::draw(Camera& camera){
    for(Mesh& mesh : m_meshes) mesh.draw(camera);
}

void MeshGroup::setMaterial(MaterialBase& material){
    for(Mesh& mesh : m_meshes) mesh.setMaterial(material);
}

void MeshGroup::setDrawMode(DrawMode mode){
    for(Mesh& mesh : m_meshes) mesh.setDrawMode(mode);
}

void MeshGroup::setPosition(float x, float y, float z){
    for(Mesh& mesh : m_meshes){
        //get current mesh matrix
        glm::mat4 meshMatrix = mesh.getModelMatrix();
        //multiply the original mesh position to the new one to not overriding it
        mesh.setModelMatrix(meshMatrix * Transform::translate(x,y,z));
    };
}

void MeshGroup::setRotation(float degree, float x, float y, float z){
    for(Mesh& mesh : m_meshes){
        glm::mat4 meshMatrix = mesh.getModelMatrix();
        mesh.setModelMatrix(meshMatrix * Transform::rotate(degree, x, y, z));
    };
}

void MeshGroup::setScale(float x, float y, float z){
    for(Mesh& mesh : m_meshes){
        glm::mat4 meshMatrix = mesh.getModelMatrix();
        mesh.setModelMatrix(meshMatrix * Transform::scale(x, y, z));
    };
}
