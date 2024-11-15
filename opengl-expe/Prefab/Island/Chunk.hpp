//
//  Chunk.hpp
//  opengl-expe
//
//  Created by EL KHANTOUR Nassim on 09/11/2024.
//

#ifndef Chunk_hpp
#define Chunk_hpp
#include "../PrefabBase.h"
#include "../../Mesh/Vertex.h"
#include "../../Mesh/VertexList.hpp"
#include "../../Mesh/VertexGroup.hpp"

#include <glm/glm.hpp>
#include <vector>
#include <stdio.h>

struct ChunkArgs{
    float radius = 2.0f;
    int points = 24;
    float shoreDistance = 0.2f;
    float cliffDistance = 0.2f;
    float cliffDepth = 0.1f;
    float beltDepth = 1.0f;
};

struct ChunkLayers{
    VertexGroup shore;
    VertexGroup cliff;
    VertexGroup land;
    VertexGroup belt;
    VertexGroup root;
};

class Chunk : public PrefabBase {
    
public:
    
    Chunk(const ChunkArgs& args);
    ~Chunk(){};
    
    VertexList& getVertices(){  return m_vertices; }
    
private:
    
    void generate();
    
    float m_radius;
    int   m_points;
    float m_shoreDistance;
    float m_cliffDistance;
    float m_cliffDepth;
    float m_beltDepth;
    
    VertexGroup m_layers;
    VertexList m_vertices;
    

    
};

#endif /* Chunk_hpp */
