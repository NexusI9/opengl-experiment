//
//  VertexGroup.hpp
//  opengl-expe
//
//  Created by EL KHANTOUR Nassim on 11/11/2024.
//

#ifndef VertexGroup_hpp
#define VertexGroup_hpp
#include <string>
#include "./VertexList.hpp"
#include "./Vertex.h"
#include <unordered_map>


struct VertexGroupPoint{
    Vertex                      vertex;
    VertexElement               index;
};

using VertexLayer = std::vector<VertexGroupPoint>;

/**
 Vertex Group are combination of Vertex List along with index, the object is mostly use to combine Vertex List together and rearange elements accordingly
 The relationship between VertexGroup and VertexList, is similar to the one between Mesh and MeshGroup
 Also the VertexGroup is closer to a fully usable Mesh by manipulating and providing the vertices as well as respective elements
 [Vertex] => [VertexList] => [VertexGroup] => [Mesh]
 */
class VertexGroup{
    
public:
    VertexGroup() = default;
    
    void addGroup(std::string name, VertexList vertices);
    VertexLayer* getGroup(std::string name);
    
    void bridge();
    
    VertexList getVertex();
    std::vector<VertexElement> getElement();
    

private:
    
    std::unordered_map<std::string, VertexLayer> m_groups;

    
    
};



#include <stdio.h>

#endif /* VertexGroup_hpp */
