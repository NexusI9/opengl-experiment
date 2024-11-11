//
//  Chunk.cpp
//  opengl-expe
//
//  Created by EL KHANTOUR Nassim on 09/11/2024.
//

#include "Chunk.hpp"
#include "Circle.hpp"
#include "../../Utility/Debugger.hpp"
#include "../../Utility/VertexUtils.hpp"

#define _USE_MATH_DEFINES
#include <cmath>


Chunk::Chunk(const ChunkArgs& args):
m_radius(args.radius),
m_points(args.points),
m_shoreDistance(args.shoreDistance),
m_beltDepth(args.beltDepth),
m_cliffDepth(args.cliffDepth),
m_cliffDistance(args.cliffDistance){
    
    generate();
}

void Chunk::generate(){
    
    //Generate armature
    m_layers.shore.name = "shore";
    for(int p = 0; p < m_points; p++){

        Circle shore({
            .radius = m_radius,
            .points = m_points
        });
        VertexList shoreVertex = shore.getVertex();
        
        Circle land({
            .radius = m_radius - m_shoreDistance,
            .points = m_points
        });
        
        Circle cliff({
            .radius = m_radius + m_cliffDistance,
            .points = m_points
        });
        VertexList cliffVertex = cliff.getVertex();
        VertexUtils::translate(cliffVertex, glm::vec3(0.0f, 0.0f, -1.0f * m_cliffDepth));
        
        
        Circle belt({
            .radius = m_radius / 1.2f,
            .points = m_points / 2
        });
        VertexList beltVertex = belt.getVertex();
        VertexUtils::translate(beltVertex, glm::vec3(0.0f, 0.0f, -1.0f * m_beltDepth));
        
        Circle root({
            .radius = m_radius * 1 / 3,
            .points = m_points / 4
        });
        VertexList rootVertex = root.getVertex();
        VertexUtils::translate(rootVertex, glm::vec3(0.0f, 0.0f, -2.0f * m_beltDepth));
        
        
        //populate layer group
        m_layers.shore.vertex = shore.getVertex();
        m_layers.land.vertex = land.getVertex();
        m_layers.cliff.vertex = cliffVertex;
        m_layers.belt.vertex = beltVertex;
        m_layers.root.vertex = rootVertex;
        
    }
        
    m_vertices = m_layers.shore.vertex;
    
    std::vector<VertexList> layers = {
        m_layers.land.vertex,
        m_layers.cliff.vertex,
        m_layers.belt.vertex,
        m_layers.root.vertex
    };
    
    VertexUtils::concat(m_vertices, layers);
    
    
}
