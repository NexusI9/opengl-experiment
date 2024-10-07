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
#include "../Scene/Camera.hpp"
#include "./Loader.h"


class Rectangle : public Loader{
    
public:
    
    Rectangle();
    ~Rectangle();
    
    std::vector<Vertex> m_vertices;
    std::vector<GLuint> m_elements;
    std::vector<Texture> m_textures;
    
};

#endif /* Rectangle_hpp */
