//
//  Rectangle.cpp
//  opengl-expe
//
//  Created by EL KHANTOUR Nassim on 28/09/2024.
//

#include "Rectangle.hpp"
#include <glm/glm.hpp>
#include <iostream>
#include "../Utility/Constant.h"
#include "../Mesh/MeshGroup.hpp"


Rectangle::Rectangle(){
    
    std::vector<glm::vec3> positions{
        glm::vec3(-0.5f,  0.5f,   0.0f),
        glm::vec3(0.5f,   0.5f,   0.0f),
        glm::vec3(0.5f,   -0.5f,  0.0f),
        glm::vec3(-0.5f,  -0.5f,  0.0f)
    };
    
    
    std::vector<glm::vec3> normals{
        glm::vec3(0.0f,  0.0f,   1.0f),
        glm::vec3(0.0f,  0.0f,   1.0f),
        glm::vec3(0.0f,  0.0f,   1.0f),
        glm::vec3(0.0f,  0.0f,   1.0f)
    };
    
    std::vector<glm::vec3> colors{
        glm::vec3(1.0f,  0.0f,   0.0f),
        glm::vec3(0.0f,  1.0f,   0.0f),
        glm::vec3(0.0f,  0.0f,   1.0f),
        glm::vec3(1.0f,  1.0f,   1.0f)
    };
    
    
    std::vector<glm::vec2> uv{
        glm::vec2(0.0f,  0.0f),
        glm::vec2(1.0f,  0.0f),
        glm::vec2(1.0f,  1.0f),
        glm::vec2(0.0f,  1.0f)
    };
    
    for (size_t i = 0; i < positions.size(); ++i) {
        Vertex tempVertex;
        tempVertex.position = positions[i];
        tempVertex.normal = normals[i];
        tempVertex.color = colors[i];
        tempVertex.texUV = uv[i];
        vertices.push_back(tempVertex);
    }

    elements = {0, 3, 2, 2, 1, 0};

    m_meshGroup->addChild(Mesh({
        .name = "rectangle",
        .vertices = vertices,
        .elements = elements
    }));
    
}
