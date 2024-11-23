//
//  VertexGroup.hpp
//  opengl-expe
//
//  Created by EL KHANTOUR Nassim on 11/11/2024.
//

#ifndef VertexGroup_hpp
#define VertexGroup_hpp
#include <string>
#include <glm/glm.hpp>
#include "./VertexList.hpp"
#include "./Vertex.h"
#include <unordered_map>


//Separate Vertext and Elements into separate objects cause easier to manipulate vertex through VertexList
struct VertexLayer{
    std::string                name;
    VertexList                 list;
};

struct Triangle{
    const VertexElement a;
    const VertexElement b;
    const VertexElement c;
    
    Triangle(const VertexElement& a, const VertexElement& b, const VertexElement& c):a(a), b(b), c(c){}
    
    VertexElement list[3]{a, b, c};
};

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
    void fill(std::string groupName, bool invertOrder = false);
    
    std::vector<Vertex> getVertex();
    std::vector<VertexElement> getElement();

private:
    
    std::vector<VertexLayer> m_groups;
    std::vector<Vertex> m_vertices;
    std::vector<VertexElement> m_elements;
    
    VertexList::Point getClosestPoint(VertexList const& haystack, glm::vec3 needle);
    void insertTriangle(std::vector<VertexElement>& reference, Triangle triangle);

    VertexElement indexOffset(std::string name);
    VertexElement indexOffset();
    
};



#include <stdio.h>

#endif /* VertexGroup_hpp */
