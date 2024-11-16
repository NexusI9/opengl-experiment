//
//  Rectangle.hpp
//  opengl-expe
//
//  Created by EL KHANTOUR Nassim on 28/09/2024.
//

#ifndef Rectangle_hpp
#define Rectangle_hpp

#include <stdio.h>
#include <GL/glew.h>
#include <vector>

#include "../Mesh/Vertex.h"
#include "../Mesh/Mesh.hpp"
#include "../Material/Texture.hpp"
#include "./Model.h"

class Rectangle : public Model{
    
public:
    
    Rectangle();
    ~Rectangle(){};
    
    std::vector<Vertex> m_vertices;
    std::vector<VertexElement> m_elements;

};

#endif /* Rectangle_hpp */
