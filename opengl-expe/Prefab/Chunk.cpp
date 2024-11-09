//
//  Chunk.cpp
//  opengl-expe
//
//  Created by EL KHANTOUR Nassim on 09/11/2024.
//

#include "Chunk.hpp"
#include "../Utility/Debugger.hpp"
#define _USE_MATH_DEFINES
#include <cmath>


Chunk::Chunk(const ChunkArgs& args):m_radius(args.radius), m_points(args.points), m_shoreDistance(args.shoreDistance){
    
    generate();
}

void Chunk::generate(){
    
    for(int p = 0; p < m_points; p++){
        
        float index = p * 2.0f * M_PI / m_points;
        
        Vertex vert{
            .position = glm::vec3(std::sin(index) * m_radius, std::cos(index) * m_radius ,1.0f),
            .normal = glm::vec3(1.0f),
            .color = glm::vec3(0.0f),
            .texUV = glm::vec2(0.0f)
        };
        
        m_vertices.push_back(vert);
        
    }
    
}
