//
//  Chunk.cpp
//  opengl-expe
//
//  Created by EL KHANTOUR Nassim on 09/11/2024.
//

#include "Chunk.hpp"
#include "Circle.hpp"
#include "../../Utility/Debugger.hpp"

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
    Circle shore({
        .radius = m_radius,
        .points = m_points
    });
    VertexList shoreVertex = shore.getVertex();
    shoreVertex.noise( glm::vec3(1.0f, 1.0f, 0.0f) );
    
    Circle land({
        .radius = m_radius - m_shoreDistance,
        .points = m_points
    });
    VertexList landVertex = shore.getVertex();
    landVertex.noise( glm::vec3(0.5f, 0.5f, 0.0f) );
    
    Circle cliff({
        .radius = m_radius + m_cliffDistance,
        .points = m_points
    });
    VertexList cliffVertex = cliff.getVertex();
    cliffVertex.translate(glm::vec3(0.0f, 0.0f, -1.0f * m_cliffDepth));
    cliffVertex.noise( glm::vec3(1.0f, 1.0f, 0.0f) );
    
    Circle belt({
        .radius = m_radius / 1.2f,
        .points = m_points / 2
    });
    VertexList beltVertex = belt.getVertex();
    beltVertex.translate(glm::vec3(0.0f, 0.0f, -1.0f * m_beltDepth));
    beltVertex.noise( glm::vec3(1.0f, 1.0f, 0.0f) );
    
    Circle root({
        .radius = m_radius * 1 / 3,
        .points = m_points / 4
    });
    VertexList rootVertex = root.getVertex();
    rootVertex.translate(glm::vec3(0.0f, 0.0f, -2.0f * m_beltDepth));
    rootVertex.noise(glm::vec3(0.5f, 0.5f, 0.8f));
    
    //populate layer group
    //m_layers.addGroup("land",  landVertex);
    m_layers.addGroup("shore", shoreVertex);
    //m_layers.addGroup("cliff", cliffVertex);
    m_layers.addGroup("belt",  beltVertex);
    //m_layers.addGroup("root",  rootVertex);
    
    m_layers.bridge();
    
    m_vertices = m_layers.getVertex();
    m_elements = m_layers.getElement();
    m_meshGroup->addChild(Mesh({
        .name = "chunk",
        .vertices = m_vertices,
        .elements = m_elements
    }));
}
