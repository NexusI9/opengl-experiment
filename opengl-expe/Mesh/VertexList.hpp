//
//  MeshUtils.hpp
//  opengl-expe
//
//  Created by EL KHANTOUR Nassim on 10/11/2024.
//

#ifndef VertexList_hpp
#define VertexList_hpp

#include <stdio.h>
#include <vector>
#include <glm/glm.hpp>
#include "./Vertex.h"



/**
 Vertex List are simple vector of Vertex with a few modifiers utilities, useful to generate basic polygons and tweak it procedurally
 */
class VertexList{
  
public:
    
    struct Point{
        Vertex         vertex;
        VertexElement  index;
    };
    
    VertexList() = default;
    
    VertexList(std::vector<Vertex> init){
        for(VertexElement i = 0; i < init.size(); i++) m_data.push_back({ .vertex = init[i], .index = i });
    };
    
    //Transformation modifiers
    void scale(float scale);
    void translate(glm::vec3 translation);
    
    //Optimization modifiers
    void subdivide(int amount);
    void decimate(int amount);
    void simplify();
    
    //Deformation modifiers
    void smooth(float amount);
    void noise(glm::vec3 amplitude = glm::vec3(1.0f, 1.0f, 1.0f));
    
    //Organization modifiers
    void concat(std::vector<VertexList>& sources);
    void concat(VertexList& source);
    
    std::vector<glm::vec2> toVec2();
    std::vector<double> toDouble(bool x = true, bool y = true, bool z = true);
    glm::vec3 center();
    glm::vec3 min();
    glm::vec3 max();
    
    Vertex average();
    
    VertexList::Point& operator[](size_t index) { return m_data[index]; }
    const VertexList::Point& operator[](size_t index) const { return m_data[index]; }
    
    void push_back(const Vertex& vec) {
        m_data.push_back({
            .vertex = vec,
            .index = static_cast<VertexElement>(m_data.size())
        });
    }
    size_t size() const { return m_data.size(); }
    bool empty() const { return m_data.empty(); }
    void clear() { return m_data.clear(); }

    auto begin() { return m_data.begin(); }
    auto end() { return m_data.end(); }
    auto front() const { return m_data.front(); }
    auto back() const { return m_data.back(); }
    
private:
    
    std::vector<VertexList::Point> m_data;

    
};




#endif /* MeshUtils_hpp */
