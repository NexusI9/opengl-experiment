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

#include "./Vertex.h"
#include "./Mesh.hpp"
#include "./Texture.hpp"
#include "../Scene/Camera.hpp"
#include "../Scene/BaseObject.h"


class Rectangle : public BaseObject{
    
public:
    
    Rectangle();
    ~Rectangle();
    
    void draw(Camera& camera);
    
    std::vector<Vertex> m_vertices;
    std::vector<GLuint> m_elements;
    std::vector<Texture> m_textures;
    
    Mesh* m_mesh;
    
};

#endif /* Rectangle_hpp */
