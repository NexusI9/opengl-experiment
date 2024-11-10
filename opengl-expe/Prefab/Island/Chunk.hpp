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

#include <glm/glm.hpp>
#include <vector>
#include <stdio.h>

struct ChunkArgs{
    float radius = 2.0f;
    int points = 24;
    float shoreDistance = 3.0f;
    float depth = 4.0f;
};

struct ChunkLayers{
    VertexGroup shore;
    VertexGroup land;
    VertexGroup belt;
    VertexGroup root;
};

class Chunk : public PrefabBase {
    
public:
    
    Chunk(const ChunkArgs& args);
    ~Chunk(){};
    
    std::vector<Vertex>& getVertices(){  return m_vertices; }
    
private:
    
    void generate();
    float m_radius;
    int m_points;
    float m_shoreDistance;
    float m_depth;
    
    ChunkLayers m_layers;
    std::vector<Vertex> m_vertices;
    

    
};

#endif /* Chunk_hpp */
