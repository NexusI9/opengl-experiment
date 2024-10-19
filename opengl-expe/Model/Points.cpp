//
//  Point.cpp
//  opengl-expe
//
//  Created by EL KHANTOUR Nassim on 16/10/2024.
//

#include "Points.hpp"

Points::Points(std::vector<glm::vec3>& positions){
    
    //Push all positions in one mesh to reduce drawcall
    for (size_t i = 0; i < positions.size(); ++i) {
        Vertex tempVertex;
        tempVertex.position = positions[i];
        tempVertex.normal = glm::vec3(0.0f,  0.0f,   1.0f);
        tempVertex.color = glm::vec3(1.0f,  1.0f,   1.0f);
        tempVertex.texUV = glm::vec2(0.0f,  0.0f);
        m_vertices.push_back(tempVertex);
        m_elements.push_back((int) i);
    }
    
    m_elements.push_back(0); //close point mesh
    m_meshes.push_back(new Mesh(m_vertices, m_elements, m_textures));
    m_meshGroup = new MeshGroup(m_meshes);
    
}
