//
//  Chunk.hpp
//  opengl-expe
//
//  Created by EL KHANTOUR Nassim on 09/11/2024.
//

#ifndef Chunk_hpp
#define Chunk_hpp
#include "./PrefabBase.h"
#include "../Mesh/Vertex.h"

#include <glm/glm.hpp>
#include <vector>
#include <stdio.h>

struct ChunkArgs{
    float radius = 2.0f;
    int points = 24;
    float shoreDistance = 3.0f;
};

class Chunk : public PrefabBase {
    
public:
    
    Chunk(const ChunkArgs& args);
    ~Chunk(){};
    
    std::vector<Vertex> m_vertices;
    
private:
    
    void generate();
    float m_radius;
    int m_points;
    float m_shoreDistance;
    

    
};

#endif /* Chunk_hpp */
