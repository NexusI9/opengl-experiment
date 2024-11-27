//
//  Rectangle.cpp
//  opengl-expe
//
//  Created by EL KHANTOUR Nassim on 28/09/2024.
//

#include "Hexagon.hpp"

#include <glm/glm.hpp>
#include <iostream>
#define _USE_MATH_DEFINES
#include <cmath>

#include "../Utility/Constant.h"
#include "../Mesh/MeshGroup.hpp"


Hexagon::Hexagon(){
    
    //TODO: Merge with Prefab/Island/Circle 
    const float RADIUS = 1.0f;

    std::vector<glm::vec3> positions;
    for (int i = 0; i < 6; ++i) {
        float angle = 2.0f * M_PI * i / 6.0f; // Divide circle into 6 parts
        float x = RADIUS * cos(angle);
        float y = RADIUS * sin(angle);
        positions.push_back(glm::vec3(x, y, 0.0f));
    }
    
    positions.push_back(glm::vec3(0.0f, 0.0f, 0.0f));  // Add center point
    
    std::vector<glm::vec3> colors;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec2> uv;
    for (const auto& pos : positions) {
        float u = (pos.x / RADIUS + 1.0f) / 2.0f; // Normalize X
        float v = (pos.y / RADIUS + 1.0f) / 2.0f; // Normalize Y
        uv.push_back(glm::vec2(u, v));
        normals.push_back(glm::vec3(0.0f, 0.0f, 1.0f));
        colors.push_back(glm::vec3(1.0f, 1.0f, 1.0f));
    }

    
    for (size_t i = 0; i < positions.size(); ++i) {
        Vertex tempVertex;
        tempVertex.position = positions[i];
        tempVertex.normal = normals[i];
        tempVertex.color = colors[i];
        tempVertex.texUV = uv[i];
        vertices.push_back(tempVertex);
    }
    
    elements = {
        6, 0, 1,
        6, 1, 2,
        6, 2, 3,
        6, 3, 4,
        6, 4, 5,
        6, 5, 0
    };

    
}
