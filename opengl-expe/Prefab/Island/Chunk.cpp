//
//  Chunk.cpp
//  opengl-expe
//
//  Created by EL KHANTOUR Nassim on 09/11/2024.
//

#include "Chunk.hpp"
#include "../../Utility/Debugger.hpp"
#include "../../Utility/MeshUtils.hpp"

#define _USE_MATH_DEFINES
#include <cmath>


Chunk::Chunk(const ChunkArgs& args):m_radius(args.radius), m_points(args.points), m_shoreDistance(args.shoreDistance), m_depth(args.depth){
    
    generate();
}

void Chunk::generate(){
    
    //Generate Land
    m_layers.shore.name = "shore";
    for(int p = 0; p < m_points; p++){
        
        float index = p * 2.0f * M_PI / m_points;
        
        Vertex vert{
            .position = glm::vec3(std::sin(index) * m_radius, std::cos(index) * m_radius ,1.0f),
            .normal = glm::vec3(1.0f),
            .color = glm::vec3(0.0f),
            .texUV = glm::vec2(0.0f)
        };
        
        //populate layer group
        m_layers.shore.vertex.push_back(vert);
        
        //push to global vertice list
        m_vertices.push_back(vert);
        
    }
    
    MeshUtils::scale(m_layers.shore.vertex, 4.0f);
    MeshUtils::decimate(m_layers.shore.vertex, 18, DecimateType::UNIFORM);
    
    m_vertices = m_layers.shore.vertex;
    //Generate Land
    
}
