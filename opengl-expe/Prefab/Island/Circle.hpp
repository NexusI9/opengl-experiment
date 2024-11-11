//
//  Circle.hpp
//  opengl-expe
//
//  Created by EL KHANTOUR Nassim on 10/11/2024.
//

#ifndef Circle_hpp
#define Circle_hpp

#include <stdio.h>
#include <glm/glm.hpp>
#include <vector>
#include "../../Mesh/Vertex.h"
#include "../../Mesh/VertexList.hpp"
#include "../../Utility/Color.h"

struct CircleArgs{
    const float radius = 1.0f;
    const int points = 24;
    const glm::vec3 color = glm::vec3(0.0f);
};

class Circle{
    
public:
    
    Circle(const CircleArgs& args);
    ~Circle(){};
    
    VertexList getVertex(){ return m_vertex; }
    
private:
    
    float m_radius = 1.0f;
    int m_points = 24;
    glm::vec3 m_color = glm::vec3(0.0f);
    VertexList m_vertex;
    void generate();
    
};

#endif /* Circle_hpp */
