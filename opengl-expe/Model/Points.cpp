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
        vertices.push_back(tempVertex);
        elements.push_back((int) i);
    }
    
    elements.push_back(0); //close point mesh
    
}
