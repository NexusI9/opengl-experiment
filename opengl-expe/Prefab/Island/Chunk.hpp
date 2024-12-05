//
//  Chunk.hpp
//  opengl-expe
//
//  Created by EL KHANTOUR Nassim on 09/11/2024.
//

#ifndef Chunk_hpp
#define Chunk_hpp

#include "../Prefab.h"
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

class Chunk : public Prefab {
    
public:
    
    Chunk(const ChunkArgs& args);
    ~Chunk(){};
    
    std::vector<Vertex>& getVertices(){  return m_vertices; }
    VertexList getVertexList(const std::string& name){
        if(VertexLayer* layer = m_layers.getGroup(name)){
            return layer->list;
        }else{
            return VertexList(); //return empty list
        }
    }
    
private:
    
    void generate();
    
    const float m_radius;
    const int   m_points;
    const float m_shoreDistance;
    const float m_cliffDistance;
    const float m_cliffDepth;
    const float m_beltDepth;
    
    VertexGroup m_layers;
    std::vector<Vertex> m_vertices;
    std::vector<VertexElement> m_elements;
    
};

#endif /* Chunk_hpp */
