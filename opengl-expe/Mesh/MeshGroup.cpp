//
//  MeshGroup.cpp
//  opengl-expe
//
//  Created by EL KHANTOUR Nassim on 07/10/2024.
//

#include "MeshGroup.hpp"


void MeshGroup::draw(Camera& camera){
    
    for(Mesh* mesh : m_meshes) mesh->draw(camera);

}
