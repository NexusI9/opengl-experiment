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

class VertexList{
  
public:
    
    VertexList() = default;
    
    VertexList(std::initializer_list<Vertex> init):m_data(init){};
    
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
    
    Vertex& operator[](size_t index) { return m_data[index]; }
    const Vertex& operator[](size_t index) const { return m_data[index]; }

    void push_back(const Vertex& vec) { m_data.push_back(vec); }
    size_t size() const { return m_data.size(); }
    bool empty() const { return m_data.empty(); }
    void clear() { return m_data.clear(); }

    auto begin() { return m_data.begin(); }
    auto end() { return m_data.end(); }
    auto begin() const { return m_data.begin(); }
    auto end() const { return m_data.end(); }
    
private:
    
    std::vector<Vertex> m_data;
    
};

struct VertexGroup{
    std::string                 name;
    VertexList                  vertex;
    std::vector<VertexElement>  index;
};


#endif /* MeshUtils_hpp */
